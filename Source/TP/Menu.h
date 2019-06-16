// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class TP_API AMenu : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget> menuWidget;

	UUserWidget* menu;

	virtual void BeginPlay() override;
	
};
