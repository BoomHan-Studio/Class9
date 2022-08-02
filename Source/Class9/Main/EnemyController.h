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
	FTimerHandle TaskHandle;

	UPROPERTY()
	TObjectPtr<UWorld> World;

	UPROPERTY()
	TObjectPtr<AEnemy> EnemyPawn;

	UFUNCTION()
	virtual void Behave();

protected:

	UFUNCTION()
	virtual void ExecMove();

	UFUNCTION()
	virtual void ExecMonitor();
};
