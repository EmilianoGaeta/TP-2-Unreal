// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb_Spike.h"

ABomb_Spike::ABomb_Spike()
{
	originMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("Material'/Game/Models/Bombs/Materials/SpikeBall_Material.SpikeBall_Material'")).Object;
}

void ABomb_Spike::BeginPlay()
{
	Super::BeginPlay();

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnHitBomb);

	if (bombType == Spike_Bomb_Type::Movable)
		_timer = 0;
	else if (bombType == Spike_Bomb_Type::Loop)
	{
		_currentWayPoint = 0;
		_nextPoint = wayPoints[_currentWayPoint]->GetActorLocation();
		_dir = (_nextPoint - GetActorLocation()).GetUnsafeNormal();
		_sum = 1;
	}
}

void ABomb_Spike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (death)return;

	ball->SetWorldRotation(FRotator(0, ball->GetComponentRotation().Yaw + DeltaTime * 50, 0));

	if (bombType == Spike_Bomb_Type::Movable)
		Move();
	else if (bombType == Spike_Bomb_Type::Loop)
		MoveWayPoints();
}

void ABomb_Spike::Move()
{
	_timer += deltaTime;
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * deltaTime * 100);
	ball->SetRelativeLocation(FVector(0, FMath::Cos(_timer * frecuency) * amplitude, 0));
}

void ABomb_Spike::MoveWayPoints()
{
	SetActorLocation(GetActorLocation() + _dir * speed * deltaTime * 100);
	if(FVector::Distance(GetActorLocation(),_nextPoint) <= speed * deltaTime * 100)
	{
		SetActorLocation(_nextPoint);
		_currentWayPoint += _sum;
		if (_currentWayPoint <= 0 || _currentWayPoint >= wayPoints.Num() - 1)
			_sum *= -1;
		_nextPoint = wayPoints[_currentWayPoint]->GetActorLocation();
		_dir = (_nextPoint - GetActorLocation()).GetUnsafeNormal();
	}
}



