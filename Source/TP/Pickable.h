// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Pickable.generated.h"

UENUM()
enum Pickable_Type
{
	Bullet_Booster     UMETA(DisplayName = "BulletBooster"),
	Weapon_Booster        UMETA(DisplayName = "WeaponBooster"),
	Life_Booster        UMETA(DisplayName = "LifeBooster"),
};

UCLASS()
class TP_API APickable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickable();
	
	UPROPERTY(EditAnywhere)
		TEnumAsByte <Pickable_Type> type;
};
