// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bomb.h"
#include "Bomb_Wheel.generated.h"

/**
 * 
 */
UCLASS()
class TP_API ABomb_Wheel : public ABomb
{
	GENERATED_BODY()
	
public:

	ABomb_Wheel();

	UPROPERTY(BlueprintReadWrite)
		UCapsuleComponent* mesh;
	UPROPERTY(BlueprintReadWrite)
		 UStaticMeshComponent* weel;

	UPROPERTY(EditAnywhere)
		float timeToDamage;
	UPROPERTY(EditAnywhere)
		float amplitude;
	UPROPERTY(EditAnywhere)
		float weelSpeed;
	UPROPERTY(EditAnywhere)
		AActor* center;


	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnStartOverlapPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Move();

	float _timer;
	float _deltaTime;

	float _timerToDamage;
	IGetDamage* _ship;
};
