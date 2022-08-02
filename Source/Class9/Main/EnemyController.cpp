// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "EnemyController.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AEnemyController::AEnemyController()
{
	
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	EnemyPawn = Cast<AEnemy>(GetPawn());

	EnemyPawn->InitializeNode(TEXT("C0"));
	Behave();
	//UKismetSystemLibrary::PrintString(this, UKismetStringLibrary::Conv_BoolToString(GetPawn() != nullptr), true, false, FLinearColor::Red, 3.f);
}

void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyController::Behave()
{
	auto& TimerManager = World->GetTimerManager();
	TimerManager.SetTimer(TaskHandle, this, &AEnemyController::ExecMove, UKismetMathLibrary::RandomFloatInRange(EnemyPawn->MinMoveDelay, EnemyPawn->MaxMoveDelay));
	/*if (!EnemyPawn->CurrentNode.bIsToMonitor)
	{
		TimerManager.SetTimer(TaskHandle, this, &AEnemyController::ExecMove, UKismetMathLibrary::RandomFloatInRange(EnemyPawn->MinMoveDelay, EnemyPawn->MaxMoveDelay));
	}
	else
	{
		
	}*/
}

void AEnemyController::ExecMove()
{
	auto Adjs = EnemyPawn->EnemyGraph.Table[EnemyPawn->CurrentNodeName].AdjNodes;
	EnemyPawn->Move(Adjs[UKismetMathLibrary::RandomIntegerInRange(0, Adjs.Num() - 1)].NodeName);
}

void AEnemyController::ExecMonitor()
{
	
}
