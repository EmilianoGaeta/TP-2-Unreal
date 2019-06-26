// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss.h"


// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoss::Activate()
{
}

void ABoss::Death()
{
	if (deathParticle)
	{
		UWorld* world = GetWorld();
		FActorSpawnParameters parameters;
		auto p = world->SpawnActor<AMyParticle>(deathParticle, GetTransform(), parameters);
		if (deathParticuleScale != 0)
			p->SetActorScale3D(FVector(1, 1, 1) * deathParticuleScale);
	}
}

