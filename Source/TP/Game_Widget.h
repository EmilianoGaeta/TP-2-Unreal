// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Ship.h"
#include "Blueprint/UserWidget.h"
#include "Game_Widget.generated.h"

/**
 * 
 */

UCLASS()
class TP_API UGame_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float shipLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AShip* ship;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
		void SetWidget();

	UPROPERTY(BlueprintReadWrite)
		FText message;

	UFUNCTION(BlueprintCallable)
		void Unpause();

	UPROPERTY(BlueprintReadWrite)
		bool bulletsAvailable;
	UPROPERTY(BlueprintReadWrite)
		bool weaponsAvailable;

private:

	int _shipInitialLife;
};
