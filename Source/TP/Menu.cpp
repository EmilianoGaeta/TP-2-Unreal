// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu.h"
#include "Blueprint/UserWidget.h"

void AMenu::BeginPlay()
{
	Super::BeginPlay();

	if (menuWidget)
	{
		menu = CreateWidget<UUserWidget>(this, menuWidget);
		if (menu)
		{
			menu->AddToViewport();
			bShowMouseCursor = true;
		}
	}
}


