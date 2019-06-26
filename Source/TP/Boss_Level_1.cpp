// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss_Level_1.h"


// Sets default values
ABoss_Level_1::ABoss_Level_1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoss_Level_1::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < myEyesBombFirst.Num(); i++)
		myEyesBombFirst[i]->active = false;
	for (int i = 0; i < myEyesBombSecond.Num(); i++)
		myEyesBombSecond[i]->active = false;

	shield->myDeath.AddDynamic(this, &ABoss_Level_1::NextFace);
	shield->activate = false;

	_phase = 0;

	lifeInterface = life;
	death = false;

	_ship = GetWorld()->GetFirstPlayerController()->GetPawn();

	_shootTimer = 0;
	_timerHit = 0;
	hit = false;

	myMaterial = UMaterialInstanceDynamic::Create(mesh->GetMaterial(0), this);
	mesh->SetMaterial(0, myMaterial);
	myMaterial->SetVectorParameterValue("HitColor", FColor::White);

	_activate = false;
}

// Called every frame
void ABoss_Level_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!_activate) return;

	if ((float)lifeInterface / life < 0.5f && _phase == 1)
		NextFace();

	if (death)
		Death();

	auto dir = _ship->GetActorLocation() - GetActorLocation();
	SetActorRotation(FRotator(0, dir.Rotation().Yaw, 0));

	pivot->SetActorRotation(pivot->GetActorRotation() + FRotator(0, DeltaTime * pivotSpeed, 0));

	if (hit)
	{
		_timerHit += DeltaTime;
		if (_timerHit >= 0.15f)
		{
			myMaterial->SetVectorParameterValue("HitColor", FColor::White);
			hit = false;
		}
	}

	_shootTimer += DeltaTime;
	if(_shootTimer >= shootTime)
	{
		UWorld* world = GetWorld();
		for (auto i = 0; i < spawnPoints.Num(); i++)
		{
			SpawnBullet(world, bullet, spawnPoints[i]);
		}
		_shootTimer = 0;
	}
}

void ABoss_Level_1::NextFace()
{
	_phase++;
	if(_phase == 1)
	{
		for (int i = 0; i < myEyesBombFirst.Num(); i++)
			myEyesBombFirst[i]->active = true;
	}
	else if(_phase == 2)
	{
		for (int i = 0; i < myEyesBombSecond.Num(); i++)
			myEyesBombSecond[i]->active = true;
	}
}

void ABoss_Level_1::Damage(int damage)
{
	lifeInterface -= damage;
	life = lifeInterface;

	hit = true;
	_timerHit = 0;
	myMaterial->SetVectorParameterValue("HitColor", FColor::Red);

	if (lifeInterface <= 0)
		death = true;
}

void ABoss_Level_1::Death()
{
	Super::Death();

	openDoor->Activate();
	Destroy();
}

void ABoss_Level_1::Activate()
{
	Super::Activate();
	_activate = true;
	shield->activate = _activate;
}

