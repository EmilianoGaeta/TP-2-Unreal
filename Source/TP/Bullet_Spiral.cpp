// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet_Spiral.h"


void ABullet_Spiral::BeginPlay()
{
	Super::BeginPlay();
	_timer = 0;
}


void ABullet_Spiral::Move(float deltatime)
{
	Super::Move(deltatime);
	_timer += deltatime;

	bullet->SetRelativeLocation((FVector(FMath::Cos(_timer * frecuency), 0, 0) + FVector(0, FMath::Sin(_timer * frecuency), 0)) * amplitude);
}


