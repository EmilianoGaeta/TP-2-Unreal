// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bomb.h"
#include "Bomb_Chain.generated.h"

/**
 * 
 */
UCLASS()
class TP_API ABomb_Chain : public ABomb
{
	GENERATED_BODY()
	
public:

	ABomb_Chain();

	UPROPERTY(BlueprintReadWrite)
		USphereComponent* mesh;
	UPROPERTY(EditAnywhere)
		float chaseSpeed;
	UPROPERTY(EditAnywhere)
		AActor* pivot;
	UPROPERTY(EditAnywhere)
		float maxDistance;
	UPROPERTY(EditAnywhere)
		float maxAngle;

	virtual void Tick(float DeltaTime) override;
	virtual void Death() override;


protected:

	virtual void BeginPlay() override;

private:

	void Move();
	FVector nextPos;

	AActor* _player;

	float _timer;
	float _timerDeath;

	bool _dead;
};
