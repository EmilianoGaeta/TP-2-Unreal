// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "Pickable.h"
#include "Weapon.h"
#include "GetDamage.h"
#include "Runtime/Core/Public/Math/UnrealMathVectorCommon.h" 
#include "GameFramework/Character.h"    
#include "Ship.generated.h"



UCLASS()
class TP_API AShip : public ACharacter, public IWeapon, public IGetDamage
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShip();

	UPROPERTY(EditAnywhere)
		float life;
	UPROPERTY(EditAnywhere)
		float speed;

	UPROPERTY(BlueprintReadWrite)
		 UChildActorComponent*  myCamera;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent*  ship;
	UPROPERTY(BlueprintReadWrite)
		UCapsuleComponent* myMesh;
		
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class ABullet>> bullets;
	UPROPERTY(EditAnywhere)
		TArray <float> shootTimes;

	UPROPERTY(EditAnywhere)
		float cameraSpeed;

	UPROPERTY(EditAnywhere)
		float cameraShakeAmplitude;
	UPROPERTY(EditAnywhere)
		float cameraShakeCyclesDuration;
	UPROPERTY(EditAnywhere)
		float cameraShakeSpeed;
	UPROPERTY(EditAnywhere)
		float cameraShakeDuration;

	bool showMessage;
	bool pause;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent*  shielMesh;
	UPROPERTY(EditAnywhere)
		float shielMaxLife;
	float shielLife;

	float debufTime;
	float debufTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(float forward, float right);


	UFUNCTION(BlueprintCallable)
	void SetCamera(UChildActorComponent* cam, UCameraComponent* myCam);

	UFUNCTION(BlueprintCallable)
	void SetWeapons(TArray<UChildActorComponent*>  spawn);

	virtual void Damage(int damage) override;
	UPROPERTY(BlueprintReadWrite)
		int currentLife;
	UPROPERTY(BlueprintReadWrite)
		bool iAmshooting;

	FText message;

	UFUNCTION(BlueprintCallable)
		void Pause();
	UFUNCTION(BlueprintCallable)
		void SetWeapon();
	UFUNCTION(BlueprintCallable)
		void SetBullet();
	UFUNCTION(BlueprintCallable)
		void Shoot();

	int bulletsTypesAmount;
	int weaponsTypeAmount;

	UFUNCTION(BlueprintCallable)
	void DebufShoot(float duration);
	void EndDebufShoot();
	UFUNCTION(BlueprintCallable)
	void DebufMovement(float duration);
	void EndDebufMovement();

private:

	bool _hasDefubEffect;
	bool _canShoot;

	FVector _dirMovement;
	FVector _dirView;
	FVector lookDir;
	float _coolDown;

	//Ship
	void SetMovementForward(float forward);
	void SetMovementRight(float right);
	void SetDirectionForward(float forward);
	void SetDirectionRight(float right);
	void SetForward(float deltatime);

	//Camera
	FVector _cameraInitailPos;	
	void SetCameraPos(float deltatime);
	UCameraComponent* _camera;
	bool _shakeCamera;
	void ShakeCamera(float deltatime);

	//Shoot
	int indexBullet;
	int indexSpawnPoint;

	TArray<UChildActorComponent*>  currentSpawnPoints;
	TSubclassOf<class ABullet> bullet;

	TMap<int, TArray<UChildActorComponent*>> weapons;

	float _cameraShakeTimer;
	float _cameraShakeCyclesTimer;
	float _timeToReturn;
	FVector _randomCameraPos;

	float _shootTimer;

	UMaterialInterface* originMaterial;
	UMaterialInstanceDynamic* myMaterial;

	UMaterialInterface* originMaterialShiel;
	UMaterialInstanceDynamic* myMaterialShield;	

	bool _hit;
	float _hitTimer;
	void HitColor(float deltaTime);


	UFUNCTION()
		void OnOverlapBooster(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
