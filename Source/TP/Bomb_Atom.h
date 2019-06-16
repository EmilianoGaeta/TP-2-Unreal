// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "Bomb_Atom.generated.h"

/**
 * 
 */
UCLASS()
class TP_API ABomb_Atom : public ABomb
{
	GENERATED_BODY()
	

public:

	ABomb_Atom();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float timeToDamage;

	UPROPERTY(BlueprintReadWrite)
		USphereComponent* mesh;
	
protected:
	
	virtual void BeginPlay() override;

private:

	void Move();

	float _deltaTime;
	AActor* _player;

	IGetDamage* _ship;
	float _timerToDamage;

	UFUNCTION()
		void OnStartOverlapPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
