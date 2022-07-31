// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPropertiesNode.h"
#include "MapAdjTable.generated.h"

USTRUCT(BlueprintType)
struct CLASS9_API FMapAdjTableNode
{
	GENERATED_BODY()

public:

	FMapAdjTableNode();

	FORCEINLINE FMapAdjTableNode(FName Name, float Dist)
		:NodeName(Name), Distance(Dist)
	{
		
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "结点名字")
	FName NodeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "距离")
	float Distance;
};

USTRUCT(BlueprintType)
struct CLASS9_API FNodeContainer
{
	GENERATED_BODY()

public:

	FNodeContainer() = default;
	
	FORCEINLINE FNodeContainer(AMapNode* Node, FVector Vector, float Angle, bool bMonitor, uint8 Code, std::initializer_list<FMapAdjTableNode> InitList)
		:PropertiesNode(Node, Vector, Angle, bMonitor, Code), AdjNodes(InitList)
	{
		
	}

	UPROPERTY(EditAnywhere, DisplayName = "结点属性")
	FEnemyPropertiesNode PropertiesNode;

	UPROPERTY(EditAnywhere, DisplayName = "邻接表")
	TArray<FMapAdjTableNode> AdjNodes;

	/*FORCEINLINE bool operator ==(const FNodeContainer& Container) const
	{
		return PropertiesNode.BoundNode == Container.PropertiesNode.BoundNode;
	}*/
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct CLASS9_API FMapAdjTable
{
	GENERATED_BODY()

public:

	FMapAdjTable() = default;

	FORCEINLINE FMapAdjTable(std::initializer_list<TPairInitializer<const FName&, const FNodeContainer&>> InitList)
		:Table(InitList)
	{
		
	}

	UPROPERTY(EditAnywhere)
	TMap<FName, FNodeContainer> Table;
};
