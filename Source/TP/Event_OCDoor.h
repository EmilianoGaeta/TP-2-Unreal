// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Door.h"
#include "EventNode.h"
#include "Event_OCDoor.generated.h"

/**
 * 
 */
UCLASS()
class TP_API AEvent_OCDoor : public AEventNode
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		bool openDoor;
	UPROPERTY(EditAnywhere)
		TArray<ADoor*> myDoors;

	virtual void Activate() override;

protected:

	virtual void BeginPlay() override;
};
