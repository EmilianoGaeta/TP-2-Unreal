// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss_Level_3.h"


// Sets default values
ABoss_Level_3::ABoss_Level_3()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoss_Level_3::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < myEyesBombFirst.Num(); i++)
		myEyesBombFirst[i]->active = false;
	for (int i = 0; i < myEyesBombSecond.Num(); i++)
		myEyesBombSecond[i]->active = false;
	for (int i = 0; i < myEyesBombThird.Num(); i++)
		myEyesBombThird[i]->active = false;

	shield->myDeath.AddDynamic(this, &ABoss_Level_3::NextFace);
	shield->activate = false;

	_phase = 0;

	lifeInterface = life;
	death = false;

	_ship = GetWorld()->GetFirstPlayerController()->GetPawn();

	_shootTimer = 0;
	_spawnTimer = 0;
	_timerHit = 0;
	_timer = 0;
	hit = false;

	myMaterial = UMaterialInstanceDynamic::Create(mesh->GetMaterial(0), this);
	mesh->SetMaterial(0, myMaterial);
	myMaterial->SetScalarParameterValue("Hit", 0);

	_activate = false;

	_center = GetActorLocation();
	_isMoving = false;
	_return = false;
}

// Called every frame
void ABoss_Level_3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!_activate) return;

	if ((float)lifeInterface / maxLife < 0.8f && _phase == 1)
		NextFace();
	if((float)lifeInterface / maxLife < 0.4f && _phase == 2)
		NextFace();

	if (death)
		Death();

	if (_phase >= 1) 
	{
		_spawnTimer += DeltaTime;
		if (_spawnTimer >= spawnTime) 
		{
			_spawnTimer = 0;
			SpawnSpikes();
		}
	}

	auto dir = _ship->GetActorLocation() - GetActorLocation();
	SetActorRotation(FRotator(0, dir.Rotation().Yaw, 0));

	pivot->SetActorRotation(pivot->GetActorRotation() + FRotator(0, DeltaTime * pivotSpeed, 0));

	if (hit)
	{
		_timerHit += DeltaTime;
		if (_timerHit >= 0.15f)
		{
			myMaterial->SetScalarParameterValue("Hit", 0);
			hit = false;
		}
	}

	if (!_isMoving)
	{
		_shootTimer += DeltaTime;
		if (_shootTimer >= shootTime)
		{
			float random = FMath::RandRange(0, 100);
			if (_phase < 1) random = 0;

			if (random <= 40)
			{
				UWorld* world = GetWorld();
				for (auto i = 0; i < spawnPoints.Num(); i++)
				{
					SpawnBullet(world, bullet, spawnPoints[i]);
				}
				_shootTimer = 0;
			}
			else
			{
				_shootTimer = 0;
				_isMoving = true;

				_dirToMove = _ship->GetActorLocation() - GetActorLocation();
				_nextPos = GetActorLocation() + _dirToMove;
				_dirToMove = _dirToMove.GetUnsafeNormal();
			}
		}
	}
	else
		Move(DeltaTime);

	if (meshMouth->IsOverlappingActor(_ship))
	{
		_timer += DeltaTime;
		if (_timer >= 0.25f)
		{
			_timer = 0;
			Cast<IGetDamage>(_ship)->Damage(damage);
		}
	}
	else
		_timer = 0;
}

void ABoss_Level_3::SpawnSpikes()
{
	UWorld* world = GetWorld();
	FActorSpawnParameters params;
	for (int i = 0; i < spawns1.Num(); i++)
	{
		auto s = world->SpawnActor<ABomb>(spikeBomb, spawns1[i]->GetTransform(), params);
		auto sp = Cast<ABomb_Spike>(s);
		if(s)
			sp->bombType = Spike_Bomb_Type::Movable;
	}
}

void ABoss_Level_3::NextFace()
{
	_phase += 1;
	if (_phase == 1)
	{
		for (int i = 0; i < myEyesBombFirst.Num(); i++)
			myEyesBombFirst[i]->active = true;

		GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, TEXT("1"));
	}
	else if (_phase == 2)
	{
		GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, TEXT("2"));

		for (int i = 0; i < myEyesBombSecond.Num(); i++)
			myEyesBombSecond[i]->active = true;
	}
	else if(_phase == 3)
	{
		GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, TEXT("3"));

		for (int i = 0; i < myEyesBombThird.Num(); i++)
			myEyesBombThird[i]->active = true;

		UWorld* world = GetWorld();
		FActorSpawnParameters params;
		for (int i = 0; i < spawns2.Num(); i++)
		{
			world->SpawnActor<ABomb>(atomBomb, spawns2[i]->GetTransform(), params);
		}
	}
}

void ABoss_Level_3::Damage(int damage)
{
	lifeInterface -= damage;
	life = lifeInterface;

	hit = true;
	_timerHit = 0;
	myMaterial->SetScalarParameterValue("Hit", 0.7f);

	if (lifeInterface <= 0)
		death = true;
}

void ABoss_Level_3::Death()
{
	Super::Death();

	openDoor->Activate();
	Destroy();
}

void ABoss_Level_3::Activate()
{
	Super::Activate();
	_activate = true;
	shield->activate = _activate;
}

void ABoss_Level_3::Move(float deltaTime)
{
	if (!_return) 
	{
		if(FVector::Dist(_nextPos,GetActorLocation()) > deltaTime * speed * 100)
		{
			SetActorLocation(GetActorLocation() + _dirToMove * deltaTime*speed * 100);
		}
		else
		{
			SetActorLocation(_nextPos);
			_return = true;
		}
	}
	else
	{
		if (FVector::Dist(_center, GetActorLocation()) > deltaTime * speed * 100)
		{
			SetActorLocation(GetActorLocation() - _dirToMove * deltaTime*speed * 100);
		}
		else
		{
			SetActorLocation(_center);
			_return = false;
			_isMoving = false;
		}
	}
}

