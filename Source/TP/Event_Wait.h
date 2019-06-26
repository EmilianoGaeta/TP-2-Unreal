// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventNode.h"
#include "Event_Wait.generated.h"

/**
 * 
 */
UCLASS()
class TP_API AEvent_Wait : public AEventNode
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void Activate() override;

protected:

	virtual void BeginPlay() override;
	
};
