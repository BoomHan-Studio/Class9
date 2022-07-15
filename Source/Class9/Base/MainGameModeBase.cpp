// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "MainGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AMainGameModeBase::AMainGameModeBase()
	:ConsumeUnitVelovity(.2f),
	Real2GameTimeConvertRatio(9.f)
{
	BeginTime = FDateTime(1, 1, 1, 8, 0, 0, 0);
	CourseDuration = FTimespan(0, 40, 0);
	EndTime = FDateTime(1, 1, 1, 8, 40, 0);
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	EndTime = BeginTime + CourseDuration;
}

void AMainGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
