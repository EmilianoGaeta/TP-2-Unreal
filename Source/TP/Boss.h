// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "MyParticle.h"
#include "GameFramework/Actor.h"
#include "Boss.generated.h"

UCLASS()
class TP_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Death();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activate();

	UPROPERTY(EditAnywhere)
		int life;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMyParticle> deathParticle;
	UPROPERTY(EditAnywhere)
		float deathParticuleScale;
};