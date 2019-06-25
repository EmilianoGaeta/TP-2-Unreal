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
#include "GameFramework/Actor.h"
#include "Boss_Level_1.generated.h"

UCLASS()
class TP_API ABoss_Level_1 : public AActor, public IGetDamage, public IWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss_Level_1();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> bullet;
	UPROPERTY(EditAnywhere)
		TArray<ABomb_Eye*> myEyesBombFirst;
	UPROPERTY(EditAnywhere)
		TArray<ABomb_Eye*> myEyesBombSecond;
	UPROPERTY(EditAnywhere)
		AActorToDestroy* shield;
	UPROPERTY(EditAnywhere)
		int life;
	UPROPERTY(EditAnywhere)
		AActor* pivot;
	UPROPERTY(EditAnywhere)
		float pivotSpeed;
	UPROPERTY(EditAnywhere)
		float shootTime;
	UPROPERTY(EditAnywhere)
		AEvent_OCDoor* openDoor;

	UPROPERTY(BlueprintReadWrite)
		TArray<UChildActorComponent*> spawnPoints;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* mesh;

	void Activate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UMaterialInstanceDynamic* myMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Damage(int damage) override;

private:

	UFUNCTION()
		void NextFace();

	void Death(float deltaTime);

	int _phase;

	AActor* _ship;

	float _shootTimer;

	float _timerHit;
	bool hit;

	bool _activate;
};
