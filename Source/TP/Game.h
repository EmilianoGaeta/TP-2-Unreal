// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Game_Widget.h"
#include "Boss.h"
#include "Ship.h"
#include "GameFramework/PlayerController.h"
#include "Game.generated.h"

/**
 * 
 */
UCLASS()
class TP_API AGame : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget> lifeWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget> messageWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget> pauseWidget;

	UPROPERTY(EditAnywhere)
		float messageTime;

	UUserWidget* lifeW;
	UUserWidget* messageW;
	UUserWidget* pauseW;

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
		ABoss* myBoss;

private:

	AShip* ship;
	float _timer;

	APlayerController* _controler;

};
