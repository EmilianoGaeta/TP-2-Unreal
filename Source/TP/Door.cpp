// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	_initialRightDoorPos = right->RelativeLocation;
	_initialLeftDoorPos = left->RelativeLocation;
	_initialRightPos = doorRight->RelativeLocation;
	_initialLeftPos = doorLeft->RelativeLocation;

	_canOpen = close;

	_initialLife = life;
	_timer = 0;

	hitbox->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnHitPlayer);

	auto mat = hitbox->GetMaterial(0);

	if (mat)
	{
		_myMaterial = UMaterialInstanceDynamic::Create(mat, this);
		hitbox->SetMaterial(0, _myMaterial);
		_myMaterial->SetVectorParameterValue("Color", myType == DoorType::Special ? FColor::Red : FColor::Blue);
	}

	_hit = false;
	_hitTimer = 0;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (open)
		OpenDoor(DeltaTime);
	else if(close)
		CloseDoor(DeltaTime);

	if (_hit && _canOpen)
		HitColor(DeltaTime);
}

void ADoor::OpenDoor(float deltaTime)
{
	if(_timer < 1)
	{
		_timer += deltaTime / 3;
		doorRight->SetRelativeLocation(FMath::Lerp(doorRight->RelativeLocation, _initialRightDoorPos, _timer));
		doorLeft->SetRelativeLocation(FMath::Lerp(doorLeft->RelativeLocation, _initialLeftDoorPos, _timer));
	}
	else
	{
		_canOpen = false;
		open = false;
	}
}

void ADoor::CloseDoor(float deltaTime)
{
	if (_timer < 1)
	{
		_timer += deltaTime / 3;
		doorRight->SetRelativeLocation(FMath::Lerp(doorRight->RelativeLocation, _initialRightPos, _timer));
		doorLeft->SetRelativeLocation(FMath::Lerp(doorLeft->RelativeLocation, _initialLeftPos, _timer));
	}
	else
	{
		life = _initialLife;
		close = false;
	}
}

void ADoor::Close()
{
	close = true;
	open = false;
	_canOpen = false;
	_timer = 0;

	_myMaterial->SetVectorParameterValue("Color", FColor::Black);
}
void ADoor::Open()
{
	_canOpen = true;
	_timer = 0;

	_hitTimer = 0;
	_hit = false;
	_myMaterial->SetVectorParameterValue("Color", myType == DoorType::Special ? FColor::Red : FColor::Blue);
}


void ADoor::OnHitPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(_canOpen)
	{
		if(myType==DoorType::Special)
		{
			ABullet_Spiral* b = Cast<ABullet_Spiral>(OtherActor);
			if (b)
			{
				life -= b->damage;
				if (life <= 0)
				{
					open = true;
					_canOpen = false;
					_timer = 0;
					_myMaterial->SetVectorParameterValue("Color", FColor::Black);
				}
				else
				{
					_hitTimer = 0;
					_hit = true;
					_myMaterial->SetVectorParameterValue("Color", FColor::White);
				}
			}
		}
		else
		{
			ABullet* b = Cast<ABullet>(OtherActor);
			if (b)
			{
				life -= b->damage;
				if (life <= 0)
				{
					open = true;
					_canOpen = false;
					_timer = 0;
					_myMaterial->SetVectorParameterValue("Color", FColor::Black);
				}
				else
				{
					_hitTimer = 0;
					_hit = true;
					_myMaterial->SetVectorParameterValue("Color", FColor::White);
				}
			}
		}
	}
}

void ADoor::HitColor(float deltaTime)
{
	_hitTimer += deltaTime;
	if (_hitTimer >= 0.15f)
	{
		_hit = false;
		_myMaterial->SetVectorParameterValue("Color", myType == DoorType::Special ? FColor::Red : FColor::Blue);
	}
}

