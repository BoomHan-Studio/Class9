// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "PlayerPowerHandle.h"

#include "Class9/Base/MainGameModeBase.h"
#include "Class9/Base/MainPlayerState.h"
#include "Class9/Base/Protagonist.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UPlayerPowerHandle::UPlayerPowerHandle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = .04f;

	// ...
}


// Called when the game starts
void UPlayerPowerHandle::BeginPlay()
{
	Super::BeginPlay();

	// ...

	auto* World = GetWorld();
	GameModeBase = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(World));
	Protagonist = Cast<AProtagonist>(GetOwner());
	//UKismetSystemLibrary::PrintString(this, UKismetStringLibrary::Conv_BoolToString(Protagonist != nullptr));
	MainPlayerState = Cast<AMainPlayerState>(UGameplayStatics::GetPlayerState(World, 0));
}


// Called every frame
void UPlayerPowerHandle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	Protagonist->Power -= DeltaTime * Protagonist->GetUsage() * GameModeBase->GetConsumeUnitVelovity() * MainPlayerState->GetExternalInfluence();
}

float& UPlayerPowerHandle::GetPlayerPowerRef() const
{
	return Protagonist->Power;
}
