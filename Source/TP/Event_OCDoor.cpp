// Fill out your copyright notice in the Description page of Project Settings.

#include "Event_OCDoor.h"

void AEvent_OCDoor::BeginPlay()
{
	Super::BeginPlay();

	iAMActive = false;
	timer = 0;

}

void AEvent_OCDoor::Tick(float DeltaTime)
{
	if(iAMActive)
	{
		timer += DeltaTime;
		if(timer >= timeToReact)
		{
			for (int i = 0; i < myDoors.Num(); i++)
			{
				if (openDoor)
					myDoors[i]->Open();
				else
					myDoors[i]->Close();
			}
			for (int i = 0; i < myNodes.Num(); i++)
				myNodes[i]->Activate();

			iAMActive = false;
		}
	}
}

void AEvent_OCDoor::Activate()
{
	iAMActive = true;
}
