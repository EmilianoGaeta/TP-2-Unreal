// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb_Chain.h"

ABomb_Chain::ABomb_Chain()
{
	originMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("Material'/Game/Models/Bombs/Materials/BombChain_Material.BombChain_Material'")).Object;
}

void ABomb_Chain::BeginPlay()
{
	Super::BeginPlay();
	auto randomDist = FMath::RandRange((float)0, maxDistance);
	auto randomAngle = FMath::RandRange(-maxAngle, maxAngle);
	auto pos = FRotator(0, pivot->GetActorRotation().Yaw + randomAngle, 0).Vector().GetUnsafeNormal();
	nextPos = pivot->GetActorLocation() + pos * randomDist;

	_player = GetWorld()->GetFirstPlayerController()->GetPawn();
	_timer = 0;
	_timerDeath = 0;
	_dead = false;
}

void ABomb_Chain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!_dead)
		Move();
	else
	{
		_timerDeath += DeltaTime;
		if (_timerDeath >= 3)
		{
			_dead = false;
			death = false;
			lifeInterface = life;
			_timerDeath = 0;
		}
	}

	if (mesh->IsOverlappingActor(_player) && !_dead)
	{
		_timer += DeltaTime;
		if (_timer >= 0.25f)
		{
			_timer = 0;
			Cast<IGetDamage>(_player)->Damage(damage);
		}
	}
	else
		_timer = 0;
}

void ABomb_Chain::Move()
{
	float dist = (_player->GetActorLocation() - pivot->GetActorLocation()).Size();

	if (dist > maxDistance) 
	{
		if (FVector::Dist(GetActorLocation(), nextPos) <= deltaTime * speed * 100)
		{
			SetActorLocation(nextPos);
			auto randomDist = FMath::RandRange((float)0, maxDistance);
			auto randomAngle = FMath::RandRange(-maxAngle, maxAngle);
			auto pos = FRotator(0, pivot->GetActorRotation().Yaw + randomAngle, 0).Vector().GetUnsafeNormal();
			nextPos = pivot->GetActorLocation() + pos * randomDist;;
		}
		else
		{
			auto dir = (nextPos - GetActorLocation()).GetUnsafeNormal();

			SetActorRotation(FMath::Lerp(GetActorRotation(), dir.Rotation(), deltaTime * 5));
			SetActorLocation(GetActorLocation() + dir * speed * deltaTime * 100);
		}
	}
	else
	{
		auto distance = (_player->GetActorLocation() - GetActorLocation());
		auto dir = distance.GetUnsafeNormal();

		SetActorRotation(FMath::Lerp(GetActorRotation(), dir.Rotation(), deltaTime * 5));
		if (distance.Size() > 70)
			SetActorLocation(GetActorLocation() + dir * chaseSpeed * deltaTime * 100);
	}
}

void ABomb_Chain::Death()
{
	_dead = true;
}

