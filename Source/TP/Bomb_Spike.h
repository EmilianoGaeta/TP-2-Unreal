// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bomb.h"
#include "Bomb_Spike.generated.h"

/**
 * 
 */
UENUM()
enum Spike_Bomb_Type
{
	Stationary     UMETA(DisplayName = "Stationary"),
	Movable        UMETA(DisplayName = "Movable"),
	Loop           UMETA(DisplayName = "Loop"),
};

UCLASS()
class TP_API ABomb_Spike : public ABomb
{
	GENERATED_BODY()
	
public:

	ABomb_Spike();

	UPROPERTY(BlueprintReadWrite)
		USphereComponent* mesh;
	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* ball;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<Spike_Bomb_Type> bombType;

	UPROPERTY(EditAnywhere)
		TArray<AActor*> wayPoints;

	UPROPERTY(EditAnywhere)
		float amplitude;
	UPROPERTY(EditAnywhere)
		float frecuency;

	virtual void Tick(float DeltaTime) override;
	
protected:

	virtual void BeginPlay() override;

private:

	void Move();
	void MoveWayPoints();

	float _timer;

	//WayPoints
	FVector _nextPoint;
	FVector _dir;
	int _currentWayPoint;
	int _sum;
};
