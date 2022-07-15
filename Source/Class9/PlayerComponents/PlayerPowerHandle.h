// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerPowerHandle.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLASS9_API UPlayerPowerHandle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerPowerHandle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, DisplayName = "游戏模式对象")
	TObjectPtr<class AMainGameModeBase> GameModeBase;

	UPROPERTY(BlueprintReadOnly, DisplayName = "玩家对象")
	TObjectPtr<class AProtagonist> Protagonist;

	UPROPERTY(BlueprintReadOnly, DisplayName = "玩家状态对象")
	TObjectPtr<class AMainPlayerState> MainPlayerState;

	UFUNCTION(BlueprintPure, DisplayName = "获取玩家体力引用")
	float& GetPlayerPowerRef() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
