// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_Widget.h"


void UGame_Widget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	shipLife = (float)ship->currentLife / _shipInitialLife;
	message = ship->message;
}

void UGame_Widget::SetWidget()
{
	ship = Cast<AShip>(GetWorld()->GetFirstPlayerController()->GetPawn());
	_shipInitialLife = ship->life;
}

void UGame_Widget::Unpause()
{
	ship->pause = false;
}


