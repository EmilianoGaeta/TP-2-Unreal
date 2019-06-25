// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"


// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();	
	lifeInterface = life;
	death = false;
	hit = false;

	if (originMaterial)
	{
		myMaterial = UMaterialInstanceDynamic::Create(originMaterial, this);
		bomb->SetMaterial(0, myMaterial);
		myMaterial->SetScalarParameterValue("Hit", 0);
	}
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	deltaTime = DeltaTime;
	if (!death && hit)
		HitColor(DeltaTime);
	if (death)
		Death();
}

void ABomb::OnHitBomb(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABullet* b = Cast<ABullet>(OtherActor);
	if (b) return;

	AShip* ship = Cast<AShip>(OtherActor);
	if (ship)
		HitPlayer(ship);
	else
		Hit();
}

void ABomb::Hit()
{
	death = true;
}
void ABomb::HitPlayer(AShip* ship)
{
	IGetDamage* hitShip = Cast<IGetDamage>(ship);
	hitShip->Damage(damage);

	death = true;
}

void ABomb::Damage(int damage)
{
	if (!death)
	{
		if (myMaterial)
		{
			hit = true;
			hitTimer = 0;
			myMaterial->SetScalarParameterValue("Hit", 0.6);
		}

		lifeInterface -= damage;
		lifeInterface = lifeInterface > 0 ? lifeInterface : 0;

		if (lifeInterface <= 0)
			death = true;
	}
}

void ABomb::Death()
{
	myDeath.Broadcast();
	if (deathParticle) 
	{
		UWorld* world = GetWorld();
		FActorSpawnParameters parameters;
		auto p = world->SpawnActor<AMyParticle>(deathParticle, GetTransform(), parameters);
		if (deathParticuleScale != 0)
			p->SetActorScale3D(FVector(1, 1, 1) * deathParticuleScale);
		
	}
	Destroy();
}

void ABomb::HitColor(float deltaTime)
{
	hitTimer += deltaTime;
	if (hitTimer >= 0.15f) 
	{
		hit = false;
		myMaterial->SetScalarParameterValue("Hit", 0);
	}
}

