// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "EventNode.generated.h"

UCLASS()
class TP_API AEventNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventNode();

	UPROPERTY(BlueprintReadWrite)
		UBoxComponent* mesh;
	UPROPERTY(EditAnywhere)
		TArray<AEventNode*> myNodes;
	UPROPERTY(EditAnywhere)
		float timeToReact;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool iAMActive;
	float timer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activate();

private:

	UFUNCTION()
		void OnOverlapPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere)
		bool _activate;
};
