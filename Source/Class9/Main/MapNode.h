// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapNode.generated.h"

UCLASS(DisplayName = "地图结点")
class CLASS9_API AMapNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapNode();

	friend class AMainGameModeBase;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "数据", DisplayName = "在此结点的敌人集")
	TSet<TObjectPtr<class AEnemy>> EnemiesInThisNode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetNodeName, Category = "数据", DisplayName = "结点名")
	FName NodeName;

public:

	UFUNCTION(BlueprintPure, BlueprintGetter, DisplayName = "获取结点名")
	FORCEINLINE FName GetNodeName() const
	{
		return NodeName;
	}

	void AddEnemy(AEnemy* Enemy);

	void RemoveEnemy(AEnemy* Enemy);

	bool TryRemoveEnemy(AEnemy* Enemy);
};
