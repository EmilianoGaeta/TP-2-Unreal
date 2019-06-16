// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bullet.h"
#include "Bullet_Sin.generated.h"

/**
 * 
 */
UCLASS()
class TP_API ABullet_Sin : public ABullet
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* bullet;

protected:

	virtual void BeginPlay() override;

	virtual void Move(float deltatime) override;

private:

	FVector _dir;
};
