// Fill out your copyright notice in the Description page of Project Settings.

#include "Event_SpawnBombs.h"

void AEvent_SpawnBombs::BeginPlay() 
{
	Super::BeginPlay();

	iAMActive = false;
	timer = 0;
}

void AEvent_SpawnBombs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (iAMActive) 
	{
		timer += DeltaTime;
		if(timer>= timeToReact)
		{
			FActorSpawnParameters parameters;
			UWorld* w = GetWorld();
			for (int i = 0; i < spawnPoints.Num(); i++)
			{
				_amountOfBombs++;
				if (myBombSpike)
				{

					auto bs = w->SpawnActor<ABomb_Spike>(myBombSpike, spawnPoints[i]->GetActorLocation(),
						spawnPoints[i]->GetActorRotation(), parameters);
					bs->bombType = Spike_Bomb_Type::Movable;
					bs->myDeath.AddDynamic(this, &AEvent_SpawnBombs::CheckBombs);
				}
				else if(myBombWheel)
				{
					auto bw= w->SpawnActor<ABomb_Wheel>(myBombWheel, spawnPoints[i]->GetActorLocation(),
						spawnPoints[i]->GetActorRotation(), parameters);
					bw->center = center;
					bw->amplitude = amplitude;
					bw->myDeath.AddDynamic(this, &AEvent_SpawnBombs::CheckBombs);
				}
				else if(myBombAtom)
				{
					auto b = w->SpawnActor<ABomb>(myBombAtom, spawnPoints[i]->GetActorLocation(),
						spawnPoints[i]->GetActorRotation(), parameters);
					b->myDeath.AddDynamic(this, &AEvent_SpawnBombs::CheckBombs);
				}		
			}
			iAMActive = false;
		}
	}
}

void AEvent_SpawnBombs::Activate()
{
	iAMActive = true;
}

void AEvent_SpawnBombs::CheckBombs()
{
	_amountOfBombs--;
	if (_amountOfBombs <= 0) 
	{
		for (int i = 0; i < myNodes.Num(); i++)
			myNodes[i]->Activate();
	}
}
