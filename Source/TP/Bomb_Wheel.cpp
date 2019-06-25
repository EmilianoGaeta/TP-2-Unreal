// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb_Wheel.h"

ABomb_Wheel::ABomb_Wheel()
{
	originMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("Material'/Game/Models/Bombs/Materials/WheelBall_Material.WheelBall_Material'")).Object;
}


void ABomb_Wheel::BeginPlay()
{
	Super::BeginPlay();
	_timer = 0;

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABomb_Wheel::OnStartOverlapPlayer);
	mesh->OnComponentEndOverlap.AddDynamic(this, &ABomb_Wheel::OnEndOverlapPlayer);
}

void ABomb_Wheel::Tick(float DeltaTime)
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

void ABomb_Wheel::Move() 
{
	_timer += _deltaTime;

	FVector pos = center->GetActorLocation() + FVector(FMath::Cos(_timer), FMath::Sin(_timer), 0) * amplitude * 100;
	FVector currentDir = (pos - GetActorLocation()).GetUnsafeNormal();
	currentDir = FVector(currentDir.X, currentDir.Y, 0);
	SetActorLocation(GetActorLocation() + currentDir * _deltaTime * speed * 100);

	FVector dir = (center->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	dir = FMath::Lerp(GetActorRotation().Vector(), dir, _deltaTime * 5);
	SetActorRotation(dir.Rotation());

	weel->SetRelativeRotationExact(FRotator(weel->RelativeRotation.Pitch + _deltaTime * weelSpeed * 10, weel->RelativeRotation.Yaw, weel->RelativeRotation.Roll));
}

void ABomb_Wheel::OnStartOverlapPlayer(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	_ship = Cast<IGetDamage>(OtherActor);
	_ship->Damage(damage);
	_timerToDamage = 0;
}

void ABomb_Wheel::OnEndOverlapPlayer(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	_ship = nullptr;
}