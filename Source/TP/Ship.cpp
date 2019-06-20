// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"


// Sets default values
AShip::AShip()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	originMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("Material'/Game/Models/Ship/Material/Ship_Material.Ship_Material'")).Object;
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();

	lookDir = GetActorForwardVector();

	_shakeCamera = false;
	_shoot = false;
	_hit = false;

	if (originMaterial)
	{
		myMaterial = UMaterialInstanceDynamic::Create(originMaterial, this);
		ship->SetMaterial(0, myMaterial);
		myMaterial->SetVectorParameterValue("HitColor", FColor::White);
	}

	bulletsTypesAmount = 1;
	weaponsTypeAmount = 1;
	_dirView = FVector(0, 0, 0);
	_dirMovement = FVector(0, 0, 0);

	currentLife = life;
	lifeInterface = life;

	myMesh->OnComponentBeginOverlap.AddDynamic(this, &AShip::OnOverlapBooster);

	showMessage = false;
	pause = false;

	GetCharacterMovement()->MaxWalkSpeed = speed * 100;
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(_dirMovement.X, _dirMovement.Y);
	SetForward(DeltaTime);

	SetCameraPos(DeltaTime);

	currentLife = lifeInterface;

	if (_shakeCamera)
		ShakeCamera(DeltaTime);

	if(_shoot)
	{
		_shootTimer += DeltaTime;
		if(_shootTimer >= coolDown)
		{
			UWorld* world = GetWorld();
			for (auto i = 0; i < currentSpawnPoints.Num(); i++)
			{
				SpawnBullet(world, bullet, currentSpawnPoints[i]);
			}
			_shootTimer = 0;
		}
	}

	if (_hit)
		HitColor(DeltaTime);
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AShip::SetMovementForward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AShip::SetMovementRight);
	PlayerInputComponent->BindAxis("DirViewX", this, &AShip::SetDirectionForward);
	PlayerInputComponent->BindAxis("DirViewY", this, &AShip::SetDirectionRight);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShip::Shoot);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AShip::Pause);
	PlayerInputComponent->BindAction("ChangeBullet", IE_Pressed, this, &AShip::SetBullet);
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &AShip::SetWeapon);
}

void AShip::Move(float forward, float right)
{
	AddMovementInput(FVector::ForwardVector, forward);
	AddMovementInput(FVector::RightVector, right);
}

void AShip::SetMovementForward(float forward)
{
	_dirMovement.X = forward;
}

void AShip::SetMovementRight(float right)
{
	_dirMovement.Y = right;
}

void AShip::SetDirectionForward(float forward)
{
	_dirView.X = forward;
}

void AShip::SetDirectionRight(float right)
{
	_dirView.Y = right;
}

void AShip::SetForward(float deltatime)
{
	if (_dirView.X != 0 || _dirView.Y != 0)
	{
		FVector dir = _dirView.GetSafeNormal();
		FVector currentDir = FMath::Lerp(GetActorForwardVector(), dir, deltatime * 15);
		SetActorRotation(FRotator(0, currentDir.Rotation().Yaw, 0));
	}
}

//Camera
void AShip::SetCamera(UChildActorComponent* cam, UCameraComponent* myCam)
{
	_cameraInitailPos = cam->GetComponentLocation() - GetActorLocation();
	myCamera = cam;
	_camera = myCam;
}

void AShip::SetCameraPos(float deltatime) 
{
	auto currentCamPos = FMath::Lerp(myCamera->GetComponentLocation(), GetActorLocation() + _cameraInitailPos, deltatime * cameraSpeed);
	myCamera->SetWorldLocation(currentCamPos);
}


//Shoot
void AShip::Shoot()
{
	if (!_shoot) 
	{
		UWorld* world = GetWorld();
		for (auto i = 0; i < currentSpawnPoints.Num(); i++)
		{
			SpawnBullet(world, bullet, currentSpawnPoints[i]);
		}
	}
	_shoot = !_shoot;
	_shootTimer = coolDown;
}

void AShip::SetBullet()
{
	indexBullet++;
	if (indexBullet >= bulletsTypesAmount) indexBullet = 0;
	if (indexBullet >= bullets.Num()) indexBullet = 0;
	bullet = bullets[indexBullet];
}

void AShip::SetWeapon()
{
	indexSpawnPoint++;
	if(indexSpawnPoint >= weaponsTypeAmount) indexSpawnPoint = 0;
	if (indexSpawnPoint >= weapons.Num()) indexSpawnPoint = 0;
	currentSpawnPoints = weapons[indexSpawnPoint];
}

void AShip::SetWeapons(TArray<UChildActorComponent*>  spawn)
{  
	indexSpawnPoint = 0;
	TArray<UChildActorComponent*> weapon;

	for (int i = 0; i < spawn.Num(); i++)
	{
		if (spawn[i])
		{
			weapon.Add(spawn[i]);
		}
		else
		{
			weapons.Add(indexSpawnPoint, weapon);
			weapon.Empty();
			indexSpawnPoint++;
		}
	}

	currentSpawnPoints = weapons[0];
	indexSpawnPoint = 0;
	bullet = bullets[0];
	indexBullet = 0;
}

void AShip::Damage(int damage)
{
	lifeInterface -= damage;

	if (lifeInterface > 0)
	{
		_shakeCamera = true;
		_cameraShakeTimer = 0;
		_cameraShakeCyclesTimer = 0;
		_timeToReturn = 0;
		_randomCameraPos = FVector(0, FMath::FRandRange(0,cameraShakeAmplitude), FMath::FRandRange(0, cameraShakeAmplitude));

		_hit = true;
		_hitTimer = 0;
		myMaterial->SetVectorParameterValue("HitColor", FColor::Red);
	}
	else
		death = true;
}

void AShip::ShakeCamera(float deltatime)
{
	_cameraShakeTimer += deltatime;
	_cameraShakeCyclesTimer += deltatime;
	
	if (_cameraShakeTimer <= cameraShakeDuration)
	{
		_camera->SetRelativeLocation(FMath::Lerp(_camera->RelativeLocation, _randomCameraPos, deltatime * cameraShakeSpeed));
		if (_cameraShakeCyclesTimer >= cameraShakeCyclesDuration) 
		{
			_randomCameraPos = FVector(0, FMath::FRandRange(0, cameraShakeAmplitude), FMath::FRandRange(0, cameraShakeAmplitude));
			_cameraShakeCyclesTimer = 0;
		}
	}
	else 
	{
		_timeToReturn += deltatime * cameraShakeSpeed;
		_camera->SetRelativeLocation(FMath::Lerp(_camera->RelativeLocation, FVector(0, 0, 0), _timeToReturn));

		if (_timeToReturn >= 1)
			_shakeCamera = false;
	}
}

void AShip::HitColor(float deltaTime)
{
	_hitTimer += deltaTime;
	if (_hitTimer >= 0.2f)
	{
		_hit = false;
		myMaterial->SetVectorParameterValue("HitColor", FColor::White);
	}
}

void AShip::OnOverlapBooster(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto b = Cast<APickable>(OtherActor);
	if (b)
	{
		if (b->type == Pickable_Type::Bullet_Booster)
		{
			showMessage = true;
			message = FText::FromString(FString(TEXT("MEJORA DE MUNICION")));
			bulletsTypesAmount++;
		}
		else if(b->type == Pickable_Type::Weapon_Booster)
		{
			showMessage = true;
			message = FText::FromString(FString(TEXT("MEJORA DE ARMA")));
			weaponsTypeAmount++;
		}
		else
		{
			lifeInterface += life / 3;
			if (lifeInterface > life) lifeInterface = life;
		}

		b->Destroy();
	}
}

void AShip::Pause()
{
	pause = !pause;
}