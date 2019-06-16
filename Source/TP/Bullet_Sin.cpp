// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet_Sin.h"

void ABullet_Sin::BeginPlay()
{
	Super::BeginPlay();

	auto auxPos = _character->GetActorLocation() - _character->GetActorForwardVector() * (GetActorLocation() - _character->GetActorLocation()).Size() * 4;

	_dir = (GetActorLocation() - auxPos).GetUnsafeNormal();
	_dir = FVector(_dir.X, _dir.Y, 0);
}


void ABullet_Sin::Move(float deltatime)
{
	SetActorLocation(GetActorLocation() + _dir * speed * deltatime * 100);
}
