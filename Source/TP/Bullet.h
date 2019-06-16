// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "GetDamage.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TP_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere)
		float speed;
	UPROPERTY(EditAnywhere)
		int damage;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Move(float deltatime);

	APawn* _character;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHitBullet(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
