// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Bullet.h"
#include "Ship.h"
#include "Weapon.h"
#include "Bomb.h"
#include "Bomb_Eye.generated.h"

/**
 * 
 */
UENUM()
enum Eye_Bomb_Type
{
	BulletWeapon     UMETA(DisplayName = "BulletWeapon"),
	LaserWeapon        UMETA(DisplayName = "LaserWeapon"),
};

UCLASS()
class TP_API ABomb_Eye : public ABomb, public IWeapon
{
	GENERATED_BODY()
	
public:

	ABomb_Eye();

	virtual void Tick(float DeltaTime) override;
	virtual void Death() override;

	UFUNCTION(BlueprintCallable)
		void SetBombEye(UChildActorComponent*  p, UChildActorComponent*  spawn, UStaticMeshComponent* e, UParticleSystemComponent* l);

	UPROPERTY(EditAnywhere)
	TEnumAsByte<Eye_Bomb_Type> bombType;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> bullet;

		
	UPROPERTY(EditAnywhere)
		float laserDistance;
	UPROPERTY(EditAnywhere)
		float timeToRevive;

	UPROPERTY(EditAnywhere)
		float rotationSpeed;
	UPROPERTY(EditAnywhere)
		float shootTime;

	UPROPERTY(EditAnywhere)
		float anlgeOfMovement;
	UPROPERTY(EditAnywhere)
		float laserDamageTime;

	bool active;

protected:

	virtual void BeginPlay() override;

private:

	AActor* _player;
	bool _dead;

	void Aim();
	void Shoot();
	void Laser();

	float _deltaTime;

	//Shoot
	float _timer;

	void Revive();

	UChildActorComponent*  _spawnPoint;
	UStaticMeshComponent* _eye;
	UParticleSystemComponent* _laser;
	UChildActorComponent*  _pivot;

	int dir;

	FVector GetLaserDistance();

	AShip* _ship;
	float _laserDamageTimer;
};
