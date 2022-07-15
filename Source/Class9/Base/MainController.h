// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Protagonist.h"
#include "GameFramework/PlayerController.h"
#include "MainController.generated.h"

/**
 * 
 */
UCLASS()
class CLASS9_API AMainController : public APlayerController
{
	GENERATED_BODY()


public:

	AMainController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

protected:

	UFUNCTION()
	void TurnLeft();

	UFUNCTION()
	void TurnRight();

	UFUNCTION()
	void AimBegin();

	UFUNCTION()
	void AimEnd();

	UFUNCTION()
	void LeftPretendBegin();

	UFUNCTION()
	void LeftPretendEnd();

	UFUNCTION()
	void RightPretendBegin();

	UFUNCTION()
	void RightPretendEnd();

	UPROPERTY(BlueprintReadOnly, DisplayName = "玩家对象")
	TObjectPtr<AProtagonist> Protagonist;
};
