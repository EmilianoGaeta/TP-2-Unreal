// Fill out your copyright notice in the Description page of Project Settings.

#include "EventNode.h"


// Sets default values
AEventNode::AEventNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventNode::BeginPlay()
{
	Super::BeginPlay();
	if(mesh) mesh->OnComponentBeginOverlap.AddDynamic(this, &AEventNode::OnOverlapPlayer);
}

// Called every frame
void AEventNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEventNode::OnOverlapPlayer(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(_activate)
	{
		for (int i = 0; i < myNodes.Num(); i++)
			myNodes[i]->Activate();

		Destroy();
	}
}

void AEventNode::Activate()
{
	_activate = true;
}

