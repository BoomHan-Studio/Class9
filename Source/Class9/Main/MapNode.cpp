// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "MapNode.h"
#include "Enemy.h"

// Sets default values
AMapNode::AMapNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

