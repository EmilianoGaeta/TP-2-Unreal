// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"


// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	UStaticMeshComponent* mesh = FindComponentByClass<UStaticMeshComponent>();
	if (mesh)
		mesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnHitBullet);

	UWorld* world = GetWorld();
	if (world) _character = world->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_character)
	{
		auto distance = FVector::Distance(_character->GetActorLocation(), GetActorLocation());
		if (distance > 3000)
			Destroy();
	}

    Move(DeltaTime);
}

void ABullet::OnHitBullet(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	IGetDamage* damageInterface = Cast<IGetDamage>(OtherActor);
	if (damageInterface)
		damageInterface->Damage(damage);

	Destroy();
}

void ABullet::Move(float deltatime)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * deltatime * 100);
}
