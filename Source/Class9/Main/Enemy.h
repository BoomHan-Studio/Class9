// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "Class9/Base/MainGameModeBase.h"
#include "Class9/Structs/MapAdjTable.h"
#include "Class9/Structs/MapGraph.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnterNode, AMapNode*, From);

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "数据", DisplayName = "敌人图表")
	FMapAdjTable EnemyGraph;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "对象", DisplayName = "游戏模式对象")
	TObjectPtr<class AMainGameModeBase> GameModeBase;

	UFUNCTION(BlueprintPure, DisplayName = "获取地图结点键值对")
	FORCEINLINE TMap<FName, AMapNode*>& GetMapNodesKvp() const
	{
		return GameModeBase->MapNodesKvp;
	}

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达C0时(委托)")
	FEnterNode WhenEnterC0;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达C1时(委托)")
	FEnterNode WhenEnterC1;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达C2时(委托)")
	FEnterNode WhenEnterC2;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达C3时(委托)")
	FEnterNode WhenEnterC3;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达C4时(委托)")
	FEnterNode WhenEnterC4;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达C5时(委托)")
	FEnterNode WhenEnterC5;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达C6时(委托)")
	FEnterNode WhenEnterC6;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达C7时(委托)")
	FEnterNode WhenEnterC7;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达L0时(委托)")
	FEnterNode WhenEnterL0;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达L1时(委托)")
	FEnterNode WhenEnterL1;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达L2时(委托)")
	FEnterNode WhenEnterL2;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达R0时(委托)")
	FEnterNode WhenEnterR0;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达R1时(委托)")
	FEnterNode WhenEnterR1;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达H0时(委托)")
	FEnterNode WhenEnterH0;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当抵达H1时(委托)")
	FEnterNode WhenEnterH1;


	/*UFUNCTION(BlueprintCallable)
	virtual void OnEnterC0()
	{
		
	}*/
};
