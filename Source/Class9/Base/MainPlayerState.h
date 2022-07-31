// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Protagonist.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CLASS9_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AMainPlayerState();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(BlueprintReadOnly, DisplayName = "玩家对象")
	TObjectPtr<AProtagonist> Protagonist;

	UPROPERTY(BlueprintReadOnly, DisplayName = "World对象")
	TObjectPtr<UWorld> World;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "状态", DisplayName = "状态代码")
	uint8 StateCode;

	UPROPERTY(VisibleAnywhere, Category = "状态|输入", DisplayName = "伪装按键是否按下")
	bool bIsAimKeyPressed;

	UFUNCTION()
	FORCEINLINE void OnAimKeyPressed()
	{
		bIsAimKeyPressed = true;
	}

	UFUNCTION()
	FORCEINLINE void OnAimKeyReleased()
	{
		bIsAimKeyPressed = false;
	}

public:

	UFUNCTION(BlueprintPure, Category = "状态", DisplayName = "玩家是否闲置")
	bool IsPlayerIdle() const;

	UFUNCTION(BlueprintPure, Category = "状态", DisplayName = "玩家是否转向")
	bool IsPlayerTurning() const;

	UFUNCTION(BlueprintPure, Category = "状态", DisplayName = "玩家是否集中")
	bool IsPlayerAiming() const;

	UFUNCTION(BlueprintPure, Category = "状态", DisplayName = "玩家是否左伪装")
	bool IsPlayerLeftPretending() const;

	UFUNCTION(BlueprintPure, Category = "状态", DisplayName = "玩家是否右伪装")
	bool IsPlayerRightPretending() const;

	UFUNCTION(BlueprintPure, Category = "状态", DisplayName = "玩家是否伪装")
	bool IsPlayerPretending() const;

	UFUNCTION(BlueprintPure, Category = "状态", DisplayName = "玩家是否受罚")
	bool IsPlayerPunished() const;

protected:

	UFUNCTION()
	void SetPlayerTurning();

	UFUNCTION()
	void ResetPlayerTurning();

	UFUNCTION()
	void SetPlayerAiming();

	UFUNCTION()
	void ResetPlayerAiming();

	UFUNCTION()
	void SetPlayerLeftPretending();

	UFUNCTION()
	void ResetPlayerLeftPretending();

	UFUNCTION()
	void SetPlayerRightPretending();

	UFUNCTION()
	void ResetPlayerRightPretending();

	UFUNCTION()
	void SetPlayerPunished();

	UFUNCTION()
	void ResetPlayerPunished();

	UFUNCTION()
	bool CanPlayerEnterIdle() const;

	UFUNCTION()
	bool CanPlayerEnterTurning() const;

	UFUNCTION()
	bool CanPlayerTurnLeft() const;

	UFUNCTION()
	bool CanPlayerTurnRight() const;

	UFUNCTION()
	bool CanPlayerEnterAiming() const;

	UFUNCTION()
	bool CanPlayerEnterPretending() const;

protected:

	UFUNCTION()
	void OnTurnLeftInvoke();

	UFUNCTION()
	void OnTurnRightInvoke();

	UFUNCTION()
	void OnAimBeginInvoke();

	UFUNCTION()
	void OnAimEndInvoke();

	UFUNCTION()
	void OnLeftPretendBeginInvoke();

	UFUNCTION()
	void OnLeftPretendEndInvoke();

	UFUNCTION()
	void OnRightPretendBeginInvoke();

	UFUNCTION()
	void OnRightPretendEndInvoke();

public:

	UFUNCTION(BlueprintPure, Category = "状态", DisplayName = "获取玩家方位")
	EPlayerDirection GetPlayerDirection() const;

	UFUNCTION(BlueprintPure, Category = "状态", DisplayName = "获取玩家负担")
	FORCEINLINE float GetPlayerUsage() const
	{
		return Protagonist->GetUsage();
	}

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetExternalInfluence, DisplayName = "外部影响")
	float PowerExternalInfluence;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, DisplayName = "外部影响集")
	TMap<FName, float> PEISet;

	UFUNCTION()
	void RefreshPEI();

	UFUNCTION()
	void UpdatePEI(float Ratio);

	UFUNCTION()
	void UpdatePEI2(float OldRatio, float NewRatio);

public:

	UFUNCTION(BlueprintGetter, DisplayName = "获取外部影响", meta = (CompactNodeTitle))
	FORCEINLINE float GetExternalInfluence() const
	{
		return PowerExternalInfluence;
	}
	
	UFUNCTION(BlueprintCallable, DisplayName = "更新影响因子")
	void UpdateInfluence(UObject* Caller, FName InName, float Ratio);

	UFUNCTION(BlueprintCallable, DisplayName = "移除影响因子")
	void RemoveInfluence(UObject* Caller, FName InName);
};
