// Copyright @2021 BoomHan Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerDirection : uint8
{
	Backward UMETA(DisplayName = "后"),
	Left UMETA(DisplayName = "左"),
	Forward UMETA(DisplayName = "前"),
	Right UMETA(DisplayName = "右"),
};

/**
 * 对照表：
 * 00000000=闲置
 * 00000001=转向
 * 00000010=集中
 * 00000100=左伪装
 * 00001000=右伪装
 * 00001100=左右伪装
 * 00010000=受罚
 */
UENUM(BlueprintType)
enum class EProtagonistState : uint8
{
	Idle = 0 UMETA(DisplayName = "闲置"),
	Turning = 1 UMETA(DisplayName = "转向"),
	Aiming = 2 UMETA(DisplayName = "集中"),
	LeftPretending = 4 UMETA(DisplayName = "左伪装"),
	RightPretending = 8 UMETA(DisplayName = "右伪装"),
	Punished = 16 UMETA(DisplayName = "受罚"),
};