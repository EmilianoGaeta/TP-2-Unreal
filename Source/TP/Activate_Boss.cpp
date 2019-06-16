// Fill out your copyright notice in the Description page of Project Settings.

#include "Activate_Boss.h"

void AActivate_Boss::BeginPlay()
{
	Super::BeginPlay();

	iAMActive = false;
	timer = 0;

}

void AActivate_Boss::Tick(float DeltaTime)
{
	if (iAMActive)
	{
		timer += DeltaTime;
		if (timer >= timeToReact)
		{
			boss->Activate();
			iAMActive = false;
		}
	}
}

void AActivate_Boss::Activate()
{
	iAMActive = true;
}



