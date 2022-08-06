// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class CLASS9_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	AEnemyController();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY()
	FTimerHandle BehaviourHandle;

	UPROPERTY()
	FTimerHandle TaskHandle;

	UPROPERTY()
	FTimerHandle TaskEndHandle;

	FTimerDelegate BehaviourDelegate;
	
	FTimerDelegate MoveDelegate;

	FTimerDelegate MonitorDelegate;

	FTimerDelegate MonitorEndDelegate;

	UPROPERTY()
	TObjectPtr<UWorld> World;

	UPROPERTY()
	TObjectPtr<AEnemy> EnemyPawn;

	UFUNCTION()
	virtual void Behave();

	UFUNCTION()
	FORCEINLINE void FinishTask(float DeltaSeconds);

protected:

	UFUNCTION()
	virtual void ExecMove();

	UFUNCTION()
	virtual void ExecMonitor();

	UFUNCTION()
	virtual void ExecEndMonitor();

	UFUNCTION(BlueprintCallable, DisplayName = "处理监听结果")
	virtual void HandleMonitorResult(uint8 MonitorCode);

protected:

	UFUNCTION()
	bool ShouldMonitor() const;

	
};
