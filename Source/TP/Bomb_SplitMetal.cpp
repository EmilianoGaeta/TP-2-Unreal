// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb_SplitMetal.h"

ABomb_SplitMetal::ABomb_SplitMetal()
{
	originMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("Material'/Game/Models/Bombs/Materials/SplitMetalBall_Material.SplitMetalBall_Material'")).Object;
}

void ABomb_SplitMetal::BeginPlay()
{
	Super::BeginPlay();

	_currentWayPoint = 0;
	_nextPoint = wayPoints[_currentWayPoint]->GetActorLocation();
	_dir = (_nextPoint - GetActorLocation()).GetUnsafeNormal();
	_sum = 1;

	_timer = 0;

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABomb_SplitMetal::OnStartOverlapPlayer);
	mesh->OnComponentEndOverlap.AddDynamic(this, &ABomb_SplitMetal::OnEndOverlapPlayer);
}

void ABomb_SplitMetal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	saw->SetWorldRotation(FRotator(0, saw->GetComponentRotation().Yaw + DeltaTime * 200, 0));
	if (_ship)
	{
		_timerToDamage += DeltaTime;
		if (_timerToDamage >= timeToDamage)
		{
			_timerToDamage = 0;
			_ship->Damage(damage);
		}
	}

	if (!_dead) 
		MoveWayPoints();
	else
	{
		_timer += DeltaTime;
		if (_timer >= 4)
		{
			_dead = false;
			death = false;
			lifeInterface = life;
			_timer = 0;
		}
	}
}

void ABomb_SplitMetal::OnStartOverlapPlayer(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	_ship = Cast<IGetDamage>(OtherActor);
	if (_ship) 
	{
		_ship->Damage(damage);
		_timerToDamage = 0;
	}
}

void ABomb_SplitMetal::OnEndOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	_ship = nullptr;
}

void ABomb_SplitMetal::MoveWayPoints()
{
	SetActorLocation(GetActorLocation() + _dir * speed * deltaTime * 100);
	if (FVector::Distance(GetActorLocation(), _nextPoint) <= speed * deltaTime * 100)
	{
		SetActorLocation(_nextPoint);
		_currentWayPoint += _sum;
		if (_currentWayPoint <= 0 || _currentWayPoint >= wayPoints.Num() - 1)
			_sum *= -1;
		_nextPoint = wayPoints[_currentWayPoint]->GetActorLocation();
		_dir = (_nextPoint - GetActorLocation()).GetUnsafeNormal();
	}
}

void ABomb_SplitMetal::Death()
{
	_dead = true;
}


