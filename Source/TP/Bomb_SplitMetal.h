// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bomb.h"
#include "Bomb_SplitMetal.generated.h"

/**
 * 
 */
UCLASS()
class TP_API ABomb_SplitMetal : public ABomb
{
	GENERATED_BODY()

public:

	ABomb_SplitMetal();

	virtual void Tick(float DeltaTime) override;
	virtual void Death() override;

	UPROPERTY(EditAnywhere)
		float timeToDamage;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> wayPoints;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* saw;
	UPROPERTY(BlueprintReadWrite)
		USphereComponent* mesh;

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnStartOverlapPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void MoveWayPoints();

	bool _dead;
	float _timer;
	
	//WayPoints
	FVector _nextPoint;
	FVector _dir;
	int _currentWayPoint;
	int _sum;

	IGetDamage* _ship;
	float _timerToDamage;
};
