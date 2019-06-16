// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Bomb.h"
#include "Bomb_Spike.h"
#include "Bomb_Wheel.h"
#include "EventNode.h"
#include "Event_SpawnBombs.generated.h"

/**
 * 
 */
UCLASS()
class TP_API AEvent_SpawnBombs : public AEventNode
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABomb> myBombSpike;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABomb> myBombWheel;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABomb> myBombAtom;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> spawnPoints;
	UPROPERTY(EditAnywhere)
		AActor* center;
	UPROPERTY(EditAnywhere)
		float amplitude;

	virtual void Tick(float DeltaTime) override;

	virtual void Activate() override;

protected:

	virtual void BeginPlay() override;
	
private:

	int _amountOfBombs;

	UFUNCTION()
		void CheckBombs();
};
