// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb_Eye.h"

ABomb_Eye::ABomb_Eye()
{
	originMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("Material'/Game/Models/Bombs/Materials/EyeBall_Material.EyeBall_Material'")).Object;
	active = true;
}


void ABomb_Eye::BeginPlay()
{
	Super::BeginPlay();

	_player = GetWorld()->GetFirstPlayerController()->GetPawn();
	_timer = 0;
}

void ABomb_Eye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	_deltaTime = DeltaTime;

	if (!active) return;

	if(!_dead)
	{
		Aim();
		if (bombType == Eye_Bomb_Type::BulletWeapon)
			Shoot();
		else
		{
			if (_ship) 
			{
				_laserDamageTimer += DeltaTime;
				if(_laserDamageTimer >= laserDamageTime)
				{
					Cast<IGetDamage>(_ship)->Damage(damage);
					_laserDamageTimer = 0;
				}
			}

			Laser();
		}
	}
	else 
	{
		if (bombType == Eye_Bomb_Type::LaserWeapon)
		{
			_timer += DeltaTime;
			if (_timer >= timeToRevive) 
			{
				_timer = 0;
				Revive();
			}

		}
	}
}

void ABomb_Eye::Aim() 
{

	if (bombType == Eye_Bomb_Type::BulletWeapon)
	{
		auto dirToWatch = _player->GetActorLocation() - GetActorLocation();
		SetActorRotation(FRotator(0, dirToWatch.Rotation().Yaw, 0));

	}
	else
	{
		_pivot->SetRelativeRotationExact(FRotator(0, _pivot->RelativeRotation.Yaw + _deltaTime * rotationSpeed * dir, 0));
		if (_pivot->RelativeRotation.Yaw >= anlgeOfMovement / 2 || _pivot->RelativeRotation.Yaw <= -anlgeOfMovement / 2) 
		{
			_pivot->SetRelativeRotationExact(FRotator(0, (anlgeOfMovement / 2) * dir, 0));
			dir *= -1;
		}
	}
}

void ABomb_Eye::Shoot()
{
	_timer += _deltaTime;
	if(_timer >= shootTime)
	{
		UWorld* world = GetWorld();
		if(world) SpawnBullet(world, bullet, _spawnPoint);
		_timer = 0;
	}
}

void ABomb_Eye::Laser()
{
	_laser->SetBeamSourcePoint(0, _spawnPoint->GetComponentLocation(), 0);
	_laser->SetBeamTargetPoint(0, GetLaserDistance(), 0);
}

FVector ABomb_Eye::GetLaserDistance()
{
	FVector d = _pivot->GetComponentLocation() + _pivot->GetForwardVector() * 100 * laserDistance;

	FHitResult* hitResult = new FHitResult();
	FVector startTrace = _spawnPoint->GetComponentLocation();
	FVector endTrace = d;
	FCollisionQueryParams* col = new FCollisionQueryParams();

	if(GetWorld()->LineTraceSingleByChannel(*hitResult,startTrace,endTrace, ECC_Visibility, *col))
	{
		d = hitResult->ImpactPoint;
		_ship = Cast<AShip>(hitResult->Actor);

		if (!_ship)
			_laserDamageTimer = laserDamageTime;
	}
	else 
	{
		_ship = nullptr;
		_laserDamageTimer = laserDamageTime;
	}

	return d;
}

void ABomb_Eye::Death()
{
	myDeath.Broadcast();
    _laser->SetActive(false);
	_dead = true;
}

void ABomb_Eye::Revive()
{
	_laser->SetActive(true);
	_eye->SetRelativeRotationExact(FRotator(0, 0, 0));

	_dead = false;
	death = false;
	lifeInterface = life;
}

void ABomb_Eye::SetBombEye(UChildActorComponent*  p, UChildActorComponent*  spawn, UStaticMeshComponent* e, UParticleSystemComponent* l)
{
	_pivot = p;
	_laser = l;
	_spawnPoint = spawn;
	_eye = e;

	if (bombType == Eye_Bomb_Type::BulletWeapon) 
	{
		_laser->SetActive(false);
		_eye->SetRelativeRotationExact(FRotator(0, 180, 0));
	}
	else
	{
		_laser->SetActive(true);
		_eye->SetRelativeRotationExact(FRotator(0, 0, 0));
		dir = 1;
	}
}