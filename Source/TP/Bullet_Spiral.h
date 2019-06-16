// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bullet.h"
#include "Bullet_Spiral.generated.h"

/**
 * 
 */
UCLASS()
class TP_API ABullet_Spiral : public ABullet
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* bullet;

	UPROPERTY(EditAnywhere)
		float frecuency;

	UPROPERTY(EditAnywhere)
		float amplitude;
	
protected:

	virtual void BeginPlay() override;

	virtual void Move(float deltatime) override;
	
private:

	float _timer;
};
