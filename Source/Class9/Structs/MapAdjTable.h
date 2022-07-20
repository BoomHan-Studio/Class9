// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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

	//FNodeContainer();

	UPROPERTY(EditAnywhere)
	TArray<FMapAdjTableNode> Nodes;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct CLASS9_API FMapAdjTable
{
	GENERATED_BODY()

public:

	//FMapAdjTable();

	UPROPERTY(EditAnywhere)
	TMap<FName, FNodeContainer> Table;
};
