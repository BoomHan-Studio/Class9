// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "Class9/Base/MainGameModeBase.h"
#include "Class9/Structs/EnemyPropertiesNode.h"
#include "Class9/Structs/MapAdjTable.h"
#include "Class9/Structs/MapGraph.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FEnterNode, AMapNode*, From, AMapNode*, To);

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

	UPROPERTY(BlueprintReadOnly, DisplayName = "当移动时(委托)")
	FEnterNode WhenMove;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName = "当移动时")
	void OnMove(AMapNode* From, AMapNode* To);
	void OnMove_Implementation(AMapNode* From, AMapNode* To);

	void OnRemove(AMapNode* From);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "", Category = "数据|详细属性")
	TMap<FName, FEnemyPropertiesNode> NodesMap;
	//FEnemyPropertiesNode Node;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "数据", DisplayName = "当前所在结点")
	AMapNode* CurrentNode;
};
