// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorToDestroy.h"


// Sets default values
AActorToDestroy::AActorToDestroy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	activate = true;
}

// Called when the game starts or when spawned
void AActorToDestroy::BeginPlay()
{
	Super::BeginPlay();
	lifeInterface = life;
	death = false;


	myMaterial = UMaterialInstanceDynamic::Create(mesh->GetMaterial(0), this);
	mesh->SetMaterial(0, myMaterial);
	myMaterial->SetScalarParameterValue("Hit", 0);

	_timer = 0;
	hit = false;
}

// Called every frame
void AActorToDestroy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (death)
		Death();
	else
	{
		if (hit)
		{
			_timer += DeltaTime;
			if(_timer >=  0.15f)
			{
				myMaterial->SetScalarParameterValue("Hit", 0);
				hit = true;
			}
		}
	}
}

void AActorToDestroy::Damage(int damage)
{
	if(activate)
	{
		lifeInterface -= damage;

		hit = true;
		_timer = 0;
		myMaterial->SetScalarParameterValue("Hit", 0.7f);

		if (lifeInterface <= 0)
		{
			death = true;
		}
	}
}

void AActorToDestroy::Death()
{
	myDeath.Broadcast();
	Destroy();
}

