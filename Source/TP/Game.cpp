// Fill out your copyright notice in the Description page of Project Settings.

#include "Game.h"
#include "Blueprint/UserWidget.h"


void AGame::BeginPlay()
{
	Super::BeginPlay();

	if (lifeWidget)
	{
		lifeW = CreateWidget<UUserWidget>(this, lifeWidget);
		if (lifeW)
		{
			lifeW->AddToViewport();
			auto l = Cast<UGame_Widget>(lifeW);
			if (l && myBoss)
				l->boss = myBoss;
		}
	}
	if (messageWidget)
	{
		messageW = CreateWidget<UUserWidget>(this, messageWidget);
		if (messageW) 
		{
			messageW->AddToViewport();
			messageW->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (pauseWidget)
	{
		pauseW = CreateWidget<UUserWidget>(this, pauseWidget);
		if (pauseW)
		{
			pauseW->AddToViewport();
			pauseW->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	ship = Cast<AShip>(GetWorld()->GetFirstPlayerController()->GetPawn());
	_timer = 0;

	_controler = GetWorld()->GetFirstPlayerController();
}

void AGame::Tick(float DeltaTime)
{
	if(messageW)
	{
		if (ship->showMessage)
		{
			_timer += DeltaTime;
			messageW->SetVisibility(ESlateVisibility::Visible);
			if(_timer>= messageTime)
			{
				messageW->SetVisibility(ESlateVisibility::Hidden);
				_timer = 0;
				ship->showMessage = false;
			}
		}
	}
	if(pauseW)
	{
		if (ship->pause)
			pauseW->SetVisibility(ESlateVisibility::Visible);
		else
			pauseW->SetVisibility(ESlateVisibility::Hidden);

		_controler->SetPause(ship->pause);
	}
}



