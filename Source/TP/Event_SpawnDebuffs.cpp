// Fill out your copyright notice in the Description page of Project Settings.

#include "Event_SpawnDebuffs.h"


void AEvent_SpawnDebuffs::BeginPlay()
{
	Super::BeginPlay();

	iAMActive = false;
	timer = 0;
}

void AEvent_SpawnDebuffs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (iAMActive)
	{
		timer += DeltaTime;
		if (timer >= timeToReact)
		{
			FActorSpawnParameters parameters;
			UWorld* w = GetWorld();
			for (int i = 0; i < spawnPoints.Num(); i++)
			{
				if (myDebuff)
					w->SpawnActor<ADebuff>(myDebuff, spawnPoints[i]->GetActorLocation(), spawnPoints[i]->GetActorRotation(), parameters);
			}
			iAMActive = false;
		}
	}
}

void AEvent_SpawnDebuffs::Activate()
{
	iAMActive = true;
}