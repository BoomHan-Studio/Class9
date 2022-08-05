// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "EnemyController.h"

#include "Class9/Base/MainPlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AEnemyController::AEnemyController()
{
	
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	//BehaviourDelegate.BindUObject()
	BehaviourDelegate.BindUObject(this, &AEnemyController::Behave);
	MoveDelegate.BindUObject(this, &AEnemyController::ExecMove);
	MonitorDelegate.BindUObject(this, &AEnemyController::ExecMonitor);
	MonitorEndDelegate.BindUObject(this, &AEnemyController::ExecEndMonitor);

	World = GetWorld();
	EnemyPawn = Cast<AEnemy>(GetPawn());

	EnemyPawn->InitializeNode(TEXT("C0"));
	EnemyPawn->WhenMonitorEnd.AddDynamic(this, &AEnemyController::HandleMonitorResult);
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

	float TaskDuration;

	if (!ShouldMonitor())
	{
		TaskDuration = EnemyPawn->GenerateMoveDelay();
		TimerManager.SetTimer(TaskHandle, MoveDelegate, TaskDuration, false);
	}
	else
	{
		TaskDuration = UKismetMathLibrary::RandomFloatInRange(0.25f, 0.75f);
		TimerManager.SetTimer(TaskHandle, MonitorDelegate, TaskDuration, false);
	}
	
	
}

void AEnemyController::FinishTask(float DeltaSeconds)
{
	World->GetTimerManager().SetTimer(BehaviourHandle, BehaviourDelegate, DeltaSeconds, false);
}

void AEnemyController::ExecMove()
{
	UKismetSystemLibrary::PrintString(this, TEXT("ExecMove"), true, false, FLinearColor::Blue, 10.f);
	auto Adjs = EnemyPawn->EnemyGraph.Table[EnemyPawn->CurrentNodeName].AdjNodes;
	EnemyPawn->Move(Adjs[UKismetMathLibrary::RandomIntegerInRange(0, Adjs.Num() - 1)].NodeName);

	FinishTask(0.1f);
}

void AEnemyController::ExecMonitor()
{
	UKismetSystemLibrary::PrintString(this, TEXT("ExecMonitor"), true, false, FLinearColor::Red, 10.f);
	EnemyPawn->Monitor();
	World->GetTimerManager().SetTimer(TaskEndHandle, MonitorEndDelegate, EnemyPawn->GenerateMonitorDuration(), false);
}

void AEnemyController::ExecEndMonitor()
{
	UKismetSystemLibrary::PrintString(this, TEXT("ExecEndMonitor"), true, false, FLinearColor::Green, 10.f);
	EnemyPawn->EndMonitor();
	ExecMove();
}

void AEnemyController::HandleMonitorResult(uint8 MonitorCode)
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("MonitorCode=%u,Left=%f,Right=%f,Result=%d"),
		MonitorCode, EnemyPawn->LeftPretendingDurationInSingleMonitor, EnemyPawn->RightPretendingDurationInSingleMonitor, EnemyPawn->IsMonitorQualifiedWhenMonitorEnd(MonitorCode)),
		true, true, FLinearColor::Red, 99.f);
	
	if (!EnemyPawn->IsMonitorQualifiedWhenMonitorEnd(MonitorCode))
	{
		EnemyPawn->GameModeBase->Defeat(EnemyPawn);
	}
}

bool AEnemyController::ShouldMonitor() const
{
	return EnemyPawn->CurrentNode.bIsToMonitor;
}
