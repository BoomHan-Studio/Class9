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

void AMapNode::AddEnemy(AEnemy* Enemy)
{
	EnemiesInThisNode.FindOrAdd(Enemy);
}

void AMapNode::RemoveEnemy(AEnemy* Enemy)
{
	EnemiesInThisNode.Remove(Enemy);
}

bool AMapNode::TryRemoveEnemy(AEnemy* Enemy)
{
	if (EnemiesInThisNode.Find(Enemy))
	{
		RemoveEnemy(Enemy);
		return true;
	}

	return false;
}
