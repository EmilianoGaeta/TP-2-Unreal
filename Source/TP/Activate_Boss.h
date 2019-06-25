// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Boss.h"
#include "EventNode.h"
#include "Activate_Boss.generated.h"

/**
 * 
 */
UCLASS()
class TP_API AActivate_Boss : public AEventNode
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

	virtual void Activate() override;

	UPROPERTY(EditAnywhere)
		ABoss* boss;

protected:

	virtual void BeginPlay() override;
	
	
};
