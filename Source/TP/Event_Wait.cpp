// Fill out your copyright notice in the Description page of Project Settings.

#include "Event_Wait.h"


void AEvent_Wait::BeginPlay()
{
	Super::BeginPlay();

	iAMActive = false;
	timer = 0;

}

void AEvent_Wait::Tick(float DeltaTime)
{
	if (iAMActive)
	{
		timer += DeltaTime;
		if (timer >= timeToReact)
		{
			for (int i = 0; i < myNodes.Num(); i++)
				myNodes[i]->Activate();

			iAMActive = false;
		}
	}
}

void AEvent_Wait::Activate()
{
	iAMActive = true;
}


