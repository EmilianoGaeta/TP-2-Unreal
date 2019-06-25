// Fill out your copyright notice in the Description page of Project Settings.

#include "FollowPlayer.h"


// Sets default values for this component's properties
UFollowPlayer::UFollowPlayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFollowPlayer::BeginPlay()
{
	Super::BeginPlay();

	_ship = GetWorld()->GetFirstPlayerController()->GetPawn();
	_owner = GetOwner();
	
}


// Called every frame
void UFollowPlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_dir = (_ship->GetActorLocation() - _owner->GetActorLocation()).GetSafeNormal();

	_owner->SetActorLocation(_owner->GetActorLocation() + _dir * speed);
}

