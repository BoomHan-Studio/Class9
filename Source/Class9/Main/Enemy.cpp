// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "Enemy.h"

#include "EnemyController.h"
#include "Class9/Base/MainPlayerState.h"
#include "Class9/Base/Protagonist.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemy::AEnemy()
	:EnemyGraph(
	{
		{TEXT("C0"), FNodeContainer()}, {TEXT("C1"), FNodeContainer()}, {TEXT("C2"), FNodeContainer()},
		{TEXT("C3"), FNodeContainer()}, {TEXT("C4"), FNodeContainer()}, {TEXT("C5"), FNodeContainer()},
		{TEXT("C6"), FNodeContainer()}, {TEXT("C7"), FNodeContainer()}, {TEXT("L0"), FNodeContainer()},
		{TEXT("L1"), FNodeContainer()}, {TEXT("L2"), FNodeContainer()}, {TEXT("R0"), FNodeContainer()},
		{TEXT("R1"), FNodeContainer()}, {TEXT("H0"), FNodeContainer()}, {TEXT("H1"), FNodeContainer()},
	}),
	MinMoveDelay(8.f),
	MaxMoveDelay(11.f),
	MinMonitorDuration(3.25f),
	MaxMonitorDuration(4.25f),
	ExpectedPercentage(0.15f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = .02f;

	//AIControllerClass = AEnemyController::StaticClass();

	auto& Table = EnemyGraph.Table;

	Table[TEXT("C0")] = FNodeContainer(nullptr, FVector(1350.f, -110.f, -20.f), 90.f, false, 0u, {FMapAdjTableNode(TEXT("C1"), 1.5f), FMapAdjTableNode(TEXT("C2"), 1.5f),});
	Table[TEXT("C1")] = FNodeContainer(nullptr, FVector(1350.f, -440.f, -20.f), 125.f, false, 0u, {FMapAdjTableNode(TEXT("C0"), 1.5f), FMapAdjTableNode(TEXT("C3"), 2.0f), FMapAdjTableNode(TEXT("L0"), 4.0f)});
	Table[TEXT("C2")] = FNodeContainer(nullptr, FVector(1220.f, 130.f, -70.f), 30.f, false, 0u, {FMapAdjTableNode(TEXT("C0"), 1.5f), FMapAdjTableNode(TEXT("C4"), 2.0f),});
	Table[TEXT("C3")] = FNodeContainer(nullptr, FVector(810.f, -390.f, -70.f), 60.f, false, 0u, {FMapAdjTableNode(TEXT("C1"), 2.0f), FMapAdjTableNode(TEXT("C5"), 2.5f),});
	Table[TEXT("C4")] = FNodeContainer(nullptr, FVector(470.f, 130.f, -70.f), 67.f, false, 0u, {FMapAdjTableNode(TEXT("C2"), 1.5f), FMapAdjTableNode(TEXT("C6"), 2.5f),});
	Table[TEXT("C5")] = FNodeContainer(nullptr, FVector(310.f, -390.f, -70.f), 0.f, true, uint8(EMonitorCode::Left), {FMapAdjTableNode(TEXT("C3"), 2.5f), FMapAdjTableNode(TEXT("C6"), 3.0f), FMapAdjTableNode(TEXT("C7"), 1.5f)});
	Table[TEXT("C6")] = FNodeContainer(nullptr, FVector(50.f, 170.f, -70.f), 180.f, true, uint8(EMonitorCode::Right), {FMapAdjTableNode(TEXT("C4"), 2.5f), FMapAdjTableNode(TEXT("C5"), 3.0f), FMapAdjTableNode(TEXT("C7"), 1.5f)});
	Table[TEXT("C7")] = FNodeContainer(nullptr, FVector(-190.f, -90.f, -70.f), -90.f, true, uint8(EMonitorCode::Left) | uint8(EMonitorCode::Right), {FMapAdjTableNode(TEXT("C5"), 1.5f), FMapAdjTableNode(TEXT("C6"), 1.5f),});
	
	Table[TEXT("L0")] = FNodeContainer(nullptr, FVector(1020.f, -870.f, -70.f), 320.f, false, 0u, {FMapAdjTableNode(TEXT("C1"), 4.0f), FMapAdjTableNode(TEXT("L1"), 2.0f), FMapAdjTableNode(TEXT("H0"), 12.0f)});
	Table[TEXT("L1")] = FNodeContainer(nullptr, FVector(630.f, -850.f, -70.f), 17.f, true, uint8(EMonitorCode::Left), {FMapAdjTableNode(TEXT("L0"), 2.0f), FMapAdjTableNode(TEXT("L2"), 2.0f),});
	Table[TEXT("L2")] = FNodeContainer(nullptr, FVector(230.f, -850.f, -70.f), 105.f, false, 0u, {FMapAdjTableNode(TEXT("L1"), 2.0f), FMapAdjTableNode(TEXT("H1"), 100.0f),});

	Table[TEXT("R0")] = FNodeContainer(nullptr, FVector(1290.f, 600.f, -70.f), 140.f, true, uint8(EMonitorCode::Left) | uint8(EMonitorCode::Right), {FMapAdjTableNode(TEXT("R1"), 3.5f), FMapAdjTableNode(TEXT("H0"), 14.0f),});
	Table[TEXT("R1")] = FNodeContainer(nullptr, FVector(170.f, 600.f, -70.f), 240.f, false, 0u, {FMapAdjTableNode(TEXT("R0"), 3.5f), FMapAdjTableNode(TEXT("H1"), 100.0f),});

	Table[TEXT("H0")] = FNodeContainer(nullptr, FVector(-1860.f, 170.f, -200.f), 0.f, false, 0u, {FMapAdjTableNode(TEXT("L0"), 12.0f), FMapAdjTableNode(TEXT("R0"), 14.0f),});
	Table[TEXT("H1")] = FNodeContainer(nullptr, FVector(-1860.f, 170.f, -200.f), 0.f, false, 0u, {FMapAdjTableNode(TEXT("L2"), 100.0f), FMapAdjTableNode(TEXT("R1"), 100.0f),});
	
	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMesh"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<UWorld> World = GetWorld();

	GameModeBase = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(World));
	Protagonist = Cast<AProtagonist>(UGameplayStatics::GetPlayerPawn(World, 0));
	MainPlayerState = Cast<AMainPlayerState>(UGameplayStatics::GetPlayerState(World, 0));

	auto& Table = EnemyGraph.Table;
	for (auto It = Table.CreateConstIterator(); It; ++It)
	{
		//UKismetSystemLibrary::PrintString(this, TEXT("BindNode"), true, false, FLinearColor::Green, 5.0f);
		BindNode(Table, It->Key);
	}

	WhenMove.AddDynamic(this, &AEnemy::OnMove);
	WhenMonitorBegin.AddDynamic(this, &AEnemy::OnMonitorBegin);
	WhenMonitorEnd.AddDynamic(this, &AEnemy::OnMonitorEnd);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlayerIsLeftPretending) LeftPretendingDurationInSingleMonitor += DeltaTime;
	if (bPlayerIsRightPretending) RightPretendingDurationInSingleMonitor += DeltaTime;
}

void AEnemy::BeginDestroy()
{
	Super::BeginDestroy();

	//CurrentNode.BoundNode->TryRemoveEnemy(this);
}

void AEnemy::InitializeNode(FName NodeName)
{
	CurrentNodeName = NodeName;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AEnemy::InitializeNode_Implementation, .02f, false);
}

void AEnemy::InitializeNode_Implementation()
{
	ReachNode(EnemyGraph.Table[CurrentNodeName].PropertiesNode);
}

void AEnemy::OnMove_Implementation(const FEnemyPropertiesNode& From, const FEnemyPropertiesNode& To)
{
	if (From.BoundNode) From.BoundNode->RemoveEnemy(this);
	if (To.BoundNode) To.BoundNode->AddEnemy(this);

	ReachNode(To);
	/*if (!To)
	{
		OnRemove(From);
	}
	else
	{
		From->RemoveEnemy(this);
		To->AddEnemy(this);
	}*/
}

void AEnemy::OnMonitorBegin_Implementation(uint8 MonitorCode)
{
	LeftPretendingDurationInSingleMonitor = 0.f;
	RightPretendingDurationInSingleMonitor = 0.f;
	
	if (MonitorCode & uint8(EMonitorCode::Left))
	{
		//UKismetSystemLibrary::PrintString(this, Protagonist->WhenLeftPretendBegin.ToString<UObject>(), true, false, FLinearColor::Green, 99.f);
		Protagonist->WhenLeftPretendBegin.AddDynamic(this, &AEnemy::SetLeftPretending);
		Protagonist->WhenLeftPretendEnd.AddDynamic(this, &AEnemy::ResetLeftPretending);
		if (MainPlayerState->IsPlayerLeftPretending()) SetLeftPretending();
	}
	if (MonitorCode & uint8(EMonitorCode::Right))
	{
		Protagonist->WhenRightPretendBegin.AddDynamic(this, &AEnemy::SetRightPretending);
		Protagonist->WhenRightPretendEnd.AddDynamic(this, &AEnemy::ResetRightPretending);
		if (MainPlayerState->IsPlayerLeftPretending()) SetRightPretending();
	}
}

void AEnemy::OnMonitorEnd_Implementation(uint8 MonitorCode)
{
	ResetLeftPretending();
	ResetRightPretending();
	
	if (MonitorCode | uint8(EMonitorCode::Left))
	{
		Protagonist->WhenLeftPretendBegin.RemoveDynamic(this, &AEnemy::SetLeftPretending);
		Protagonist->WhenLeftPretendEnd.RemoveDynamic(this, &AEnemy::ResetLeftPretending);
	}
	if (MonitorCode | uint8(EMonitorCode::Right))
	{
		Protagonist->WhenRightPretendBegin.RemoveDynamic(this, &AEnemy::SetRightPretending);
		Protagonist->WhenRightPretendEnd.RemoveDynamic(this, &AEnemy::ResetRightPretending);
	}
}

void AEnemy::BindNode(TMap<FName, FNodeContainer>& Map, FName Name)
{
	Map[Name].PropertiesNode.BoundNode = GameModeBase->GetNodeByName(Name);
}

void AEnemy::Move(FName NodeName)
{
	CurrentNodeName = NodeName;
	WhenMove.Broadcast(CurrentNode, EnemyGraph.Table[NodeName].PropertiesNode);
}

void AEnemy::Monitor()
{
	WhenMonitorBegin.Broadcast(CurrentNode.MonitorDirectionCode);
}

void AEnemy::EndMonitor()
{
	WhenMonitorEnd.Broadcast(CurrentNode.MonitorDirectionCode);
}

void AEnemy::ReachNode(const FEnemyPropertiesNode& To)
{
	CurrentNode = To;
	SetActorLocationAndRotation(To.Location, FRotator::MakeFromEuler(FVector(0.f, 0.f, To.ViewAngle)));
}

float AEnemy::GenerateMoveDelay() const
{
	return UKismetMathLibrary::RandomFloatInRange(MinMoveDelay, MaxMoveDelay);
}

float AEnemy::GenerateMonitorDuration() const
{
	return UKismetMathLibrary::RandomFloatInRange(MinMonitorDuration, MaxMonitorDuration);
}

bool AEnemy::IsMonitorQualifiedWhenMonitorEnd(uint8 MonitorCode)
{
	const bool bIsPretending = (MainPlayerState->GetPlayerStateCode() & (MonitorCode << 2)) == (MonitorCode << 2);
	
	//!A || A && B == !A || B
	const bool bLeftMoreThanPercentage = ((MonitorCode & uint8(EMonitorCode::Left)) == 0u) || MainPlayerState->IsPlayerLeftPretending();
	const bool bRightMoreThanPercentage = ((MonitorCode & uint8(EMonitorCode::Right)) == 0u) || MainPlayerState->IsPlayerRightPretending();
	return bIsPretending && bLeftMoreThanPercentage && bRightMoreThanPercentage;
}
