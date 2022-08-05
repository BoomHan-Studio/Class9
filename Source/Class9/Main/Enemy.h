// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "Class9/Base/MainGameModeBase.h"
#include "Class9/Structs/EnemyPropertiesNode.h"
#include "Class9/Structs/MapAdjTable.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnterNode, const FEnemyPropertiesNode&, From, const FEnemyPropertiesNode&, To);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMonitor, uint8, MonitorCode);

UCLASS(DisplayName = "敌人")
class CLASS9_API AEnemy : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, DisplayName = "初始化结点")
	void InitializeNode(FName NodeName);

protected:


	UFUNCTION()
	void InitializeNode_Implementation();

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginDestroy() override;

protected:

	UPROPERTY(EditAnywhere, Category = "数据|详细属性", DisplayName = "敌人图表")
	FMapAdjTable EnemyGraph;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "对象", DisplayName = "游戏模式对象")
	TObjectPtr<class AMainGameModeBase> GameModeBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "对象", DisplayName = "玩家对象")
	TObjectPtr<class AProtagonist> Protagonist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "对象", DisplayName = "玩家状态对象")
	TObjectPtr<class AMainPlayerState> MainPlayerState;

	UFUNCTION(BlueprintPure, DisplayName = "获取地图结点键值对")
	FORCEINLINE TMap<FName, AMapNode*>& GetMapNodesKvp() const
	{
		return GameModeBase->MapNodesKvp;
	}

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "数据", DisplayName = "当前结点名")
	FName CurrentNodeName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "数据", DisplayName = "当前所在结点")
	FEnemyPropertiesNode CurrentNode;

	UFUNCTION()
	void BindNode(TMap<FName, FNodeContainer>& Map, FName Name);

protected:

	UPROPERTY(VisibleAnywhere, Category = "骨骼网格体")
	TObjectPtr<USkeletalMeshComponent> EnemyMesh;

public:

	UPROPERTY(BlueprintReadOnly, DisplayName = "当移动时(委托)")
	FEnterNode WhenMove;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当监听开始时(委托)")
	FMonitor WhenMonitorBegin;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当监听结束时(委托)")
	FMonitor WhenMonitorEnd;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName = "当移动时")
	void OnMove(const FEnemyPropertiesNode& From, const FEnemyPropertiesNode& To);
	void OnMove_Implementation(const FEnemyPropertiesNode& From, const FEnemyPropertiesNode& To);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName = "当监听开始时")
	void OnMonitorBegin(uint8 MonitorCode);
	void OnMonitorBegin_Implementation(uint8 MonitorCode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName = "当监听结束时")
	void OnMonitorEnd(uint8 MonitorCode);
	void OnMonitorEnd_Implementation(uint8 MonitorCode);
	
	UFUNCTION(BlueprintCallable, DisplayName = "移动至结点")
	void Move(FName NodeName);

	UFUNCTION(BlueprintCallable, DisplayName = "监听")
	void Monitor();

	UFUNCTION(BlueprintCallable, DisplayName = "结束监听")
	void EndMonitor();

	UFUNCTION()
	void ReachNode(const FEnemyPropertiesNode& To);

protected:

	UPROPERTY(VisibleInstanceOnly, Category = "数据", DisplayName = "玩家在左伪装")
	bool bPlayerIsLeftPretending;

	UPROPERTY(VisibleInstanceOnly, Category = "数据", DisplayName = "玩家在右伪装")
	bool bPlayerIsRightPretending;

	UPROPERTY(VisibleInstanceOnly, Category = "数据", DisplayName = "单次监听左伪装持续时间")
	float LeftPretendingDurationInSingleMonitor;

	UPROPERTY(VisibleInstanceOnly, Category = "数据", DisplayName = "单次监听右伪装持续时间")
	float RightPretendingDurationInSingleMonitor;

	UFUNCTION()
	FORCEINLINE void SetLeftPretending()
	{
		bPlayerIsLeftPretending = true;
	}

	UFUNCTION()
	FORCEINLINE void ResetLeftPretending()
	{
		bPlayerIsLeftPretending = false;
	}

	UFUNCTION()
	FORCEINLINE void SetRightPretending()
	{
		bPlayerIsRightPretending = true;
	}

	UFUNCTION()
	FORCEINLINE void ResetRightPretending()
	{
		bPlayerIsRightPretending = false;
	}

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "数据|详细属性|基本", DisplayName = "最小移动延迟时间")
	float MinMoveDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "数据|详细属性|基本", DisplayName = "最大移动延迟时间")
	float MaxMoveDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "数据|详细属性|基本", DisplayName = "最小监视持续时间")
	float MinMonitorDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "数据|详细属性|基本", DisplayName = "最大监视持续时间")
	float MaxMonitorDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "数据|详细属性|基本", DisplayName = "预期百分比")
	float ExpectedPercentage;

	UFUNCTION(BlueprintPure, DisplayName = "生成移动延迟时间")
	virtual float GenerateMoveDelay() const;

	UFUNCTION(BlueprintPure, DisplayName = "生成监视持续时间")
	virtual float GenerateMonitorDuration() const;

	friend class AEnemyController;

protected:

	UFUNCTION()
	virtual bool IsMonitorQualifiedWhenMonitorEnd(uint8 MonitorCode);
};