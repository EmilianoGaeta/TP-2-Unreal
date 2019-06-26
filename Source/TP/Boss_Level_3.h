// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bomb.h"
#include "Bomb_Eye.h"
#include "Bullet.h"
#include "GetDamage.h"
#include "Event_OCDoor.h"
#include "Bomb_Spike.h"
#include "Bomb_Atom.h"
#include "Weapon.h"
#include "ActorToDestroy.h"
#include "Boss.h"
#include "Boss_Level_3.generated.h"

/**
 * 
 */
UCLASS()
class TP_API ABoss_Level_3 : public ABoss, public IGetDamage, public IWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoss_Level_3();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> bullet;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABomb> spikeBomb;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABomb> atomBomb;
	UPROPERTY(EditAnywhere)
		TArray<ABomb_Eye*> myEyesBombFirst;
	UPROPERTY(EditAnywhere)
		TArray<ABomb_Eye*> myEyesBombSecond;
	UPROPERTY(EditAnywhere)
		TArray<ABomb_Eye*> myEyesBombThird;
	UPROPERTY(EditAnywhere)
		AActorToDestroy* shield;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> spawns1;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> spawns2;
	UPROPERTY(EditAnywhere)
		AActor* pivot;
	UPROPERTY(EditAnywhere)
		float pivotSpeed;
	UPROPERTY(EditAnywhere)
		float shootTime;
	UPROPERTY(EditAnywhere)
		float spawnTime;
	UPROPERTY(EditAnywhere)
		AEvent_OCDoor* openDoor;

	UPROPERTY(BlueprintReadWrite)
		TArray<UChildActorComponent*> spawnPoints;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* mesh;

	virtual void Activate() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UMaterialInstanceDynamic* myMaterial;

	virtual void Death() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Damage(int damage) override;

private:

	UFUNCTION()
		void NextFace();

	int _phase;

	AActor* _ship;

	float _shootTimer;
	float _spawnTimer;

	float _timerHit;
	bool hit;

	bool _activate;
	
	void SpawnSpikes();
	
	
};
