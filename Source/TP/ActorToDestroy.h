// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GetDamage.h"
#include "GameFramework/Actor.h"
#include "ActorToDestroy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActorDeath);

UCLASS()
class TP_API AActorToDestroy : public AActor, public IGetDamage
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorToDestroy();

	UPROPERTY(EditAnywhere)
		int life;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* mesh;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FActorDeath myDeath;

	bool activate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Death();

	UMaterialInstanceDynamic* myMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Damage(int damage) override;

private:

	float _timer;
	bool hit;
};
