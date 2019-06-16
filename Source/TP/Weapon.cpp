// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

ABullet* IWeapon::SpawnBullet(UWorld* world, TSubclassOf<class ABullet>  bullet, UChildActorComponent* spawnPoints)
{
		FActorSpawnParameters parameters;
		return    world->SpawnActor<ABullet>(bullet, spawnPoints->GetComponentLocation(),
			      spawnPoints->GetComponentRotation(), parameters);
}
// Add default functionality here for any IWeapon functions that are not pure virtual.
