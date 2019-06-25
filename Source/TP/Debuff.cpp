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

	_dir = (_ship->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	SetActorLocation(GetActorLocation() + _dir * speed);
}

