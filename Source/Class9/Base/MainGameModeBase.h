// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CLASS9_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AMainGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "时间", DisplayName = "上课时间")
	FDateTime BeginTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "时间", DisplayName = "课堂持续时间")
	FTimespan CourseDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "时间", DisplayName = "下课时间(不可编辑)")
	FDateTime EndTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "数据|可调整的固定属性", DisplayName = "玩家单位时间体力消耗速度")
	float ConsumeUnitVelovity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "数据|可调整的固定属性", DisplayName = "现实-游戏时间转换比")
	float Real2GameTimeConvertRatio;

public:

	UFUNCTION(BlueprintPure, DisplayName = "获取玩家单位时间体力消耗速度", meta = (CompactNodeTitle))
	FORCEINLINE float GetConsumeUnitVelovity() const
	{
		return ConsumeUnitVelovity;
	}

	UFUNCTION(BlueprintPure, DisplayName = "获取现实-游戏时间转换比", meta = (CompactNodeTitle))
	FORCEINLINE float GetReal2GameTimeConvertRatio() const
	{
		return Real2GameTimeConvertRatio;
	}

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "数据|地图", DisplayName = "地图结点键值对")
	TMap<FName, TObjectPtr<class AMapNode>> MapNodesKvp;

	UPROPERTY(EditDefaultsOnly, Category = "类模板", DisplayName = "地图结点类")
	TSubclassOf<AMapNode> SubclassOfMapNode;

public:

	UFUNCTION(BlueprintPure, DisplayName = "根据结点名获取结点")
	AMapNode* GetNodeByName(FName InName) const;

	UFUNCTION(BlueprintPure, DisplayName = "根据结点获取结点名")
	FName GetNameByNode(AMapNode* InNode) const;
};
