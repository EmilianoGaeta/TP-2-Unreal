// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bullet.h"
#include "Bullet_Spiral.h"
#include "Bullet_Sin.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UENUM()
enum DoorType
{
	Type1     UMETA(DisplayName = "Type1"),
	Type2        UMETA(DisplayName = "Type2"),
	Type3        UMETA(DisplayName = "Type3")
};

UCLASS()
class TP_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		int life;
	UPROPERTY(EditAnywhere)
		bool open;
	UPROPERTY(EditAnywhere)
		bool close;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<DoorType> myType;
	
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* hitbox;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* doorRight;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* doorLeft;
	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* right;
	UPROPERTY(BlueprintReadWrite)
		UChildActorComponent* left;

	void Close();
	void Open();
	
private:

	bool _canOpen;
	float _timer;
	int _initialLife;

	FVector _initialRightDoorPos;
	FVector _initialLeftDoorPos;
	FVector _initialRightPos;
	FVector _initialLeftPos;

	void OpenDoor(float deltaTime);
	void CloseDoor(float deltaTime);

	UMaterialInstanceDynamic* _myMaterial;
	float _hitTimer;
	bool _hit;
	void HitColor(float deltaTime);

	UFUNCTION()
		void OnHitPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};