// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "EnemyPropertiesNode.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EMonitorCode : uint8
{
	None = 0 UMETA(DisplayName = "无"),
	Right = 1 UMETA(DisplayName = "右"),
	Left = 2 UMETA(DisplayName = "左"),
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct CLASS9_API FEnemyPropertiesNode
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly, DisplayName = "绑定结点")
	class AMapNode* BoundNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "位置坐标")
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "视野方向角")
	float ViewAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "是否为监控点")
	bool bIsToMonitor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "监控方向代码", meta = (Bitmask, BitmaskEnum = "EMonitorCode"))
	uint8 MonitorDirectionCode;

	FEnemyPropertiesNode() = default;

	FEnemyPropertiesNode(AMapNode* Node, FVector Vector, float Angle, bool bMonitor, uint8 Code);
};
