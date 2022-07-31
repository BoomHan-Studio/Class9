// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "Enemy.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
	:EnemyGraph(
	{
		{TEXT("C0"), FNodeContainer()}, {TEXT("C1"), FNodeContainer()}, {TEXT("C2"), FNodeContainer()},
		{TEXT("C3"), FNodeContainer()}, {TEXT("C4"), FNodeContainer()}, {TEXT("C5"), FNodeContainer()},
		{TEXT("C6"), FNodeContainer()}, {TEXT("C7"), FNodeContainer()}, {TEXT("L0"), FNodeContainer()},
		{TEXT("L1"), FNodeContainer()}, {TEXT("L2"), FNodeContainer()}, {TEXT("R0"), FNodeContainer()},
		{TEXT("R1"), FNodeContainer()}, {TEXT("H0"), FNodeContainer()}, {TEXT("H1"), FNodeContainer()},
	})
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto& Table = EnemyGraph.Table;
	Table[TEXT("C0")].AdjNodes = {FMapAdjTableNode(TEXT("C1"), 1.5f), FMapAdjTableNode(TEXT("C2"), 1.5f),};
	Table[TEXT("C1")].AdjNodes = {FMapAdjTableNode(TEXT("C0"), 1.5f), FMapAdjTableNode(TEXT("C3"), 2.0f), FMapAdjTableNode(TEXT("L0"), 4.0f)};
	Table[TEXT("C2")].AdjNodes = {FMapAdjTableNode(TEXT("C0"), 1.5f), FMapAdjTableNode(TEXT("C4"), 2.0f),};
	Table[TEXT("C3")].AdjNodes = {FMapAdjTableNode(TEXT("C1"), 2.0f), FMapAdjTableNode(TEXT("C5"), 2.5f),};
	Table[TEXT("C4")].AdjNodes = {FMapAdjTableNode(TEXT("C2"), 1.5f), FMapAdjTableNode(TEXT("C6"), 2.5f),};
	Table[TEXT("C5")].AdjNodes = {FMapAdjTableNode(TEXT("C3"), 2.5f), FMapAdjTableNode(TEXT("C6"), 3.0f), FMapAdjTableNode(TEXT("C7"), 1.5f)};
	Table[TEXT("C6")].AdjNodes = {FMapAdjTableNode(TEXT("C4"), 2.5f), FMapAdjTableNode(TEXT("C5"), 3.0f), FMapAdjTableNode(TEXT("C7"), 1.5f)};
	Table[TEXT("C7")].AdjNodes = {FMapAdjTableNode(TEXT("C5"), 1.5f), FMapAdjTableNode(TEXT("C6"), 1.5f),};
	
	Table[TEXT("L0")].AdjNodes = {FMapAdjTableNode(TEXT("C1"), 4.0f), FMapAdjTableNode(TEXT("L1"), 2.0f), FMapAdjTableNode(TEXT("H0"), 12.0f)};
	Table[TEXT("L1")].AdjNodes = {FMapAdjTableNode(TEXT("L0"), 2.0f), FMapAdjTableNode(TEXT("L2"), 2.0f),};
	Table[TEXT("L2")].AdjNodes = {FMapAdjTableNode(TEXT("L1"), 2.0f), FMapAdjTableNode(TEXT("H1"), 100.0f),};
	
	Table[TEXT("R0")].AdjNodes = {FMapAdjTableNode(TEXT("R1"), 3.5f), FMapAdjTableNode(TEXT("H0"), 14.0f),};
	Table[TEXT("R1")].AdjNodes = {FMapAdjTableNode(TEXT("R0"), 3.5f), FMapAdjTableNode(TEXT("H1"), 100.0f),};
	
	Table[TEXT("H0")].AdjNodes = {FMapAdjTableNode(TEXT("L0"), 12.0f), FMapAdjTableNode(TEXT("R0"), 14.0f),};
	Table[TEXT("H1")].AdjNodes = {FMapAdjTableNode(TEXT("L2"), 100.0f), FMapAdjTableNode(TEXT("R1"), 100.0f),};

	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMesh"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	GameModeBase = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	auto& Table = EnemyGraph.Table;
	for (auto It = Table.CreateConstIterator(); It; ++It)
	{
		//UKismetSystemLibrary::PrintString(this, TEXT("BindNode"), true, false, FLinearColor::Green, 5.0f);
		BindNode(Table, It->Key);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::BeginDestroy()
{
	Super::BeginDestroy();

	CurrentNode.BoundNode->RemoveEnemy(this);
}

void AEnemy::OnMove_Implementation(const FEnemyPropertiesNode& From, const FEnemyPropertiesNode& To)
{
	From.BoundNode->RemoveEnemy(this);
	To.BoundNode->AddEnemy(this);

	SetActorLocationAndRotation(To.Location, FRotator(0.f, 0.f, To.ViewAngle));
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

void AEnemy::BindNode(TMap<FName, FNodeContainer>& Map, FName Name)
{
	
	Map[Name].PropertiesNode.BoundNode = GameModeBase->GetNodeByName(Name);
}

void AEnemy::Move(FName NodeName)
{
	WhenMove.Broadcast(CurrentNode, EnemyGraph.Table[NodeName].PropertiesNode);
}