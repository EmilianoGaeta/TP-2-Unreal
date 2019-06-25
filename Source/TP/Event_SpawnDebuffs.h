// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debuff.h"
#include "EventNode.h"
#include "Event_SpawnDebuffs.generated.h"

/**
 * 
 */
UCLASS()
class TP_API AEvent_SpawnDebuffs : public AEventNode
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ADebuff> myDebuff;

	UPROPERTY(EditAnywhere)
		TArray<AActor*> spawnPoints;

	virtual void Tick(float DeltaTime) override;

	virtual void Activate() override;

protected:

	virtual void BeginPlay() override;
		
};
