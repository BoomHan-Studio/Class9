// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEnums.h"
#include "Camera/CameraComponent.h"
#include "Class9/DataStructures/CircularLinkedList.h"
#include "Class9/PlayerComponents/PlayerPowerHandle.h"
#include "GameFramework/Pawn.h"
#include "Protagonist.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerInvoke);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerAction);

UCLASS()
class CLASS9_API AProtagonist : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AProtagonist();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginDestroy() override;

	friend class AMainController;
	friend class AMainPlayerState;
	friend class UPlayerPowerHandle;

#pragma region DELEGATE_DECLARATION

public://委托

	UPROPERTY(BlueprintReadOnly, DisplayName = "当左转激活时(委托)", Category = "委托")
	FPlayerInvoke WhenTurnLeftInvoke;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当右转激活时(委托)", Category = "委托")
	FPlayerInvoke WhenTurnRightInvoke;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当集中开始激活时(委托)", Category = "委托")
	FPlayerInvoke WhenAimBeginInvoke;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当集中结束激活时(委托)", Category = "委托")
	FPlayerInvoke WhenAimEndInvoke;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当左伪装开始激活时(委托)", Category = "委托")
	FPlayerInvoke WhenLeftPretendBeginInvoke;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当左伪装结束激活时(委托)", Category = "委托")
	FPlayerInvoke WhenLeftPretendEndInvoke;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当右伪装开始激活时(委托)", Category = "委托")
	FPlayerInvoke WhenRightPretendBeginInvoke;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当右伪装结束激活时(委托)", Category = "委托")
	FPlayerInvoke WhenRightPretendEndInvoke;

	

	UPROPERTY(BlueprintReadOnly, DisplayName = "当左转开始时(委托)", Category = "委托")
	FPlayerAction WhenTurnLeftBegin;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当左转结束时(委托)", Category = "委托")
	FPlayerAction WhenTurnLeftEnd;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当右转开始时(委托)", Category = "委托")
	FPlayerAction WhenTurnRightBegin;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当右转结束时(委托)", Category = "委托")
	FPlayerAction WhenTurnRightEnd;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当集中开始激活时(委托)", Category = "委托")
	FPlayerAction WhenAimBegin;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当集中结束激活时(委托)", Category = "委托")
	FPlayerAction WhenAimEnd;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当左伪装开始激活时(委托)", Category = "委托")
	FPlayerAction WhenLeftPretendBegin;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当左伪装结束激活时(委托)", Category = "委托")
	FPlayerAction WhenLeftPretendEnd;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当右伪装开始激活时(委托)", Category = "委托")
	FPlayerAction WhenRightPretendBegin;

	UPROPERTY(BlueprintReadOnly, DisplayName = "当右伪装结束激活时(委托)", Category = "委托")
	FPlayerAction WhenRightPretendEnd;

#pragma endregion 

protected://激活绑定函数

	/*UFUNCTION()
	void TurnLeftInvoke();

	UFUNCTION()
	void TurnRightInvoke();

	UFUNCTION()
	void AimBeginInvoke();

	UFUNCTION()
	void AimEndInvoke();

	UFUNCTION()
	void LeftPretendBeginInvoke();

	UFUNCTION()
	void LeftPretendEndInvoke();

	UFUNCTION()
	void RightPretendBeginInvoke();

	UFUNCTION()
	void RightPretendEndInvoke();*/

protected://基本执行函数

	UFUNCTION()
	void TurnLeft();

	UFUNCTION()
	void TurnLeftEnd();

	UFUNCTION()
	void TurnRight();

	UFUNCTION()
	void TurnRightEnd();

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

protected://组件

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "组件", DisplayName = "玩家视角相机")
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "组件", DisplayName = "体力组件")
	TObjectPtr<UPlayerPowerHandle> PowerHandle;

protected://对象

	UPROPERTY(BlueprintReadOnly, DisplayName = "控制器对象")
	TObjectPtr<class AMainController> MainController;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "对象", DisplayName = "前相机")
	TObjectPtr<AActor> ForwardCamera;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "对象", DisplayName = "后相机")
	TObjectPtr<AActor> BackwardCamera;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "对象", DisplayName = "左相机")
	TObjectPtr<AActor> LeftCamera;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "对象", DisplayName = "右相机")
	TObjectPtr<AActor> RightCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "对象|容器", DisplayName = "相机表")
	TArray<TObjectPtr<AActor>> CameraList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "对象", DisplayName = "World对象")
	TObjectPtr<UWorld> World;

protected://数据

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "数据", DisplayName = "方向代码")
	uint8 DirectionCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "数据|详细属性", DisplayName = "转向时间")
	float TurningDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintGetter = GetPower, Category = "数据", DisplayName = "体力")
	float Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "数据|详细属性", DisplayName = "最大体力")
	float MaxPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "数据|详细属性", DisplayName = "初始负担")
	float OriginalUsage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, BlueprintGetter = GetUsage, BlueprintSetter = SetUsage, Category = "数据", DisplayName = "负担")
	float Usage;
	
	float* UsageRef;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "数据|详细属性", DisplayName = "转向负担增值")
	float TurningUsageBonus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "数据|详细属性", DisplayName = "集中负担增值")
	float AimingUsageBonus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "数据|详细属性", DisplayName = "左伪装负担增值")
	float LeftPretendingUsageBonus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "数据|详细属性", DisplayName = "右伪装负担增值")
	float RightPretendingUsageBonus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "数据|详细属性", DisplayName = "受罚负担增值")
	float PunishmentUsageBonus;

public:

	UFUNCTION(BlueprintGetter)
	float GetUsage() const;

	UFUNCTION(BlueprintCallable, BlueprintSetter)
	void SetUsage(float Usg);

	UFUNCTION(BlueprintGetter)
	FORCEINLINE float GetPower() const
	{
		return Power;
	}

protected:

	UFUNCTION()
	FORCEINLINE void UsagePlus(float Value)
	{
		Usage += Value;
	}

	UFUNCTION()
	FORCEINLINE void UsageMinus(float Value)
	{
		Usage -= Value;
	}

protected:

	UFUNCTION()
	FORCEINLINE void TurningUsageIncrease()
	{
		UsagePlus(TurningUsageBonus);
	}

	UFUNCTION()
	FORCEINLINE void TurningUsageRecover()
	{
		UsageMinus(TurningUsageBonus);
	}

	UFUNCTION()
	FORCEINLINE void AimingUsageIncrease()
	{
		UsagePlus(AimingUsageBonus);
	}

	UFUNCTION()
	FORCEINLINE void AimingUsageRecover()
	{
		UsageMinus(AimingUsageBonus);
	}

	UFUNCTION()
	FORCEINLINE void LeftPretendingUsageIncrease()
	{
		UsagePlus(LeftPretendingUsageBonus);
	}

	UFUNCTION()
	FORCEINLINE void LeftPretendingUsageRecover()
	{
		UsageMinus(LeftPretendingUsageBonus);
	}

	UFUNCTION()
	FORCEINLINE void RightPretendingUsageIncrease()
	{
		UsagePlus(RightPretendingUsageBonus);
	}

	UFUNCTION()
	FORCEINLINE void RightPretendingUsageRecover()
	{
		UsageMinus(RightPretendingUsageBonus);
	}

	UFUNCTION()
	FORCEINLINE void PunishmentUsageIncrease()
	{
		UsagePlus(PunishmentUsageBonus);
	}

	UFUNCTION()
	FORCEINLINE void PunishmentUsageRecover()
	{
		UsageMinus(PunishmentUsageBonus);
	}
};
