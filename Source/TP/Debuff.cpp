// Fill out your copyright notice in the Description page of Project Settings.

#include "Debuff.h"


// Sets default values
ADebuff::ADebuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADebuff::BeginPlay()
{
	Super::BeginPlay();
	_ship = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void ADebuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto distance = FVector::Distance(_ship->GetActorLocation(), GetActorLocation());
	if (distance < 4000) 
	{

		myRing->AddLocalRotation(FRotator(DeltaTime * 120, 0, 0));

		_dir = (_ship->GetActorLocation() - GetActorLocation()).GetSafeNormal();

		auto currentDir = FMath::Lerp(GetActorRotation().Vector(), _dir, DeltaTime * 10);
		SetActorRotation(FRotator(0, currentDir.Rotation().Yaw, 0));

		SetActorLocation(GetActorLocation() + currentDir * speed);
	}
}

