// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Ship.h"
#include "GetDamage.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBombDeath);

UCLASS()
class TP_API ABomb : public AActor, public IGetDamage
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	UPROPERTY(EditAnywhere)
		int life;
	UPROPERTY(EditAnywhere)
		int damage;
	UPROPERTY(EditAnywhere)
		float speed;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* bomb;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FBombDeath myDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float deltaTime;

	UMaterialInterface* originMaterial;
	UMaterialInstanceDynamic* myMaterial;

	bool hit;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Damage(int damage) override;
	virtual void Death();

	UFUNCTION()
		void OnHitBomb(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Hit();
	virtual void HitPlayer(AShip* ship);

	float hitTimer;
	void HitColor(float deltaTime);
};
