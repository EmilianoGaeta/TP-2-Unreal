// Fill out your copyright notice in the Description page of Project Settings.

#include "Game_Widget.h"


void UGame_Widget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	shipLife = (float)ship->currentLife / _shipInitialLife;
	shipShield = (float)ship->shielLife / ship->shielMaxLife;
	shipDebuf = (float)ship->debufTimer / ship->debufTime;
	message = ship->message;
	bulletsAvailable = ship->bulletsTypesAmount > 1;
	weaponsAvailable = ship->weaponsTypeAmount > 1;

	if (boss)
	{
		bossLife = (float)boss->life / boss->maxLife;
		bossExist = boss->bossActivated;
	}
	else
	{
		bossExist = false;
	}
}

void UGame_Widget::SetWidget()
{
	ship = Cast<AShip>(GetWorld()->GetFirstPlayerController()->GetPawn());
	_shipInitialLife = ship->life;
	bulletsAvailable = ship->bulletsTypesAmount > 1;
	weaponsAvailable = ship->weaponsTypeAmount > 1;
}

void UGame_Widget::Unpause()
{
	ship->pause = false;
}


