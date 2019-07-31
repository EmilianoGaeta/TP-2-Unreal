// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bomb.h"
#include "Bomb_Eye.h"
#include "Bullet.h"
#include "GetDamage.h"
#include "Event_OCDoor.h"
#include "Weapon.h"
#include "ActorToDestroy.h"
#include "Boss.h"
#include "Boss_Level_5.generated.h"

/**
 * 
 */
UCLASS()
class TP_API ABoss_Level_5 : public ABoss, public IGetDamage, public IWeapon
{
	GENERATED_BODY()
public:

	ABoss_Level_5();

	UPROPERTY(EditAnywhere)
		int damage;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> bullet;
	UPROPERTY(EditAnywhere)
		TArray<ABomb_Eye*> myEyeBombs;
	UPROPERTY(EditAnywhere)
		AActorToDestroy* shield;
	UPROPERTY(EditAnywhere)
		AActor* pivot;
	UPROPERTY(EditAnywhere)
		float pivotSpeed;
	UPROPERTY(EditAnywhere)
		float shootTime;
	UPROPERTY(EditAnywhere)
		TArray<AActor *> fireBalls;
	UPROPERTY(EditAnywhere)
		float fireMaxDistanece;
	UPROPERTY(EditAnywhere)
		float fireMinDistanece;
	UPROPERTY(EditAnywhere)
		float fireBallSpeed;
	UPROPERTY(EditAnywhere)
		AEvent_OCDoor* openDoor;

	UPROPERTY(BlueprintReadWrite)
		TArray<UChildActorComponent*> spawnPoints;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* mesh;

	virtual void Activate() override;

protected:

	virtual void BeginPlay() override;

	UMaterialInstanceDynamic* myMaterial;

	virtual void Death() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void Damage(int damage) override;

private:

	UFUNCTION()
		void NextFace();

	int _phase;

	AActor* _ship;

	float _shootTimer;

	float _timerHit;
	bool hit;

	bool _activate;
	
	float _timer;	
	float _currentFireDistance;
	int _fireDir;
};
