// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "MainController.h"

#include "MainGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AMainController::AMainController()
{
	
}

void AMainController::BeginPlay()
{
	Super::BeginPlay();

	Protagonist = Cast<AProtagonist>(GetPawn());
	Protagonist->MainController = this;
}

void AMainController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMainController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("TurnLeft"), IE_Pressed, this, &AMainController::TurnLeft);
	InputComponent->BindAction(TEXT("TurnRight"), IE_Pressed, this, &AMainController::TurnRight);
	InputComponent->BindAction(TEXT("Aim"), IE_Pressed, this, &AMainController::AimBegin);
	InputComponent->BindAction(TEXT("Aim"), IE_Released, this, &AMainController::AimEnd);
	InputComponent->BindAction(TEXT("LeftPretend"), IE_Pressed, this, &AMainController::LeftPretendBegin);
	InputComponent->BindAction(TEXT("LeftPretend"), IE_Released, this, &AMainController::LeftPretendEnd);
	InputComponent->BindAction(TEXT("RightPretend"), IE_Pressed, this, &AMainController::RightPretendBegin);
	InputComponent->BindAction(TEXT("RightPretend"), IE_Released, this, &AMainController::RightPretendEnd);
}

void AMainController::TurnLeft()
{
	Protagonist->WhenTurnLeftInvoke.Broadcast();
}

void AMainController::TurnRight()
{
	Protagonist->WhenTurnRightInvoke.Broadcast();
}

void AMainController::AimBegin()
{
	Protagonist->WhenAimBeginInvoke.Broadcast();
}

void AMainController::AimEnd()
{
	Protagonist->WhenAimEndInvoke.Broadcast();
}

void AMainController::LeftPretendBegin()
{
	Protagonist->WhenLeftPretendBeginInvoke.Broadcast();
}

void AMainController::LeftPretendEnd()
{
	Protagonist->WhenLeftPretendEndInvoke.Broadcast();
}

void AMainController::RightPretendBegin()
{
	Protagonist->WhenRightPretendBeginInvoke.Broadcast();
}

void AMainController::RightPretendEnd()
{
	Protagonist->WhenRightPretendEndInvoke.Broadcast();
}
