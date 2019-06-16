// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb_Atom.h"

ABomb_Atom::ABomb_Atom()
{
	originMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("Material'/Game/Models/Bombs/Materials/BombAtomShield_Material.BombAtomShield_Material'")).Object;
}

void ABomb_Atom::BeginPlay()
{
	Super::BeginPlay();

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnHitBomb);
	_player = GetWorld()->GetFirstPlayerController()->GetPawn();

	bomb->OnComponentBeginOverlap.AddDynamic(this, &ABomb_Atom::OnStartOverlapPlayer);
	bomb->OnComponentEndOverlap.AddDynamic(this, &ABomb_Atom::OnEndOverlapPlayer);
}

void ABomb_Atom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_deltaTime = DeltaTime;
	Move();

	if (_ship)
	{
		_timerToDamage += DeltaTime;
		if (_timerToDamage >= timeToDamage)
		{
			_timerToDamage = 0;
			_ship->Damage(damage);
		}
	}

}

void ABomb_Atom::Move()
{
	auto dir = (_player->GetActorLocation() - GetActorLocation()).GetUnsafeNormal();
	dir = FVector(dir.X, dir.Y, 0);
	SetActorLocation(GetActorLocation() + dir * speed *_deltaTime * 100);
}

void ABomb_Atom::OnStartOverlapPlayer(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	_ship = Cast<IGetDamage>(OtherActor);
	_ship->Damage(damage);
	_timerToDamage = 0;
}

void ABomb_Atom::OnEndOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	_ship = nullptr;
}

