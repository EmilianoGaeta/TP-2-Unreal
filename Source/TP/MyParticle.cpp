// Fill out your copyright notice in the Description page of Project Settings.

#include "MyParticle.h"


// Sets default values
AMyParticle::AMyParticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyParticle::BeginPlay()
{
	Super::BeginPlay();
	_timer = 0;
}

// Called every frame
void AMyParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (destroyTime > 0)
	{
		_timer += DeltaTime;
		if (_timer >= destroyTime)
			Destroy();
	}
}

