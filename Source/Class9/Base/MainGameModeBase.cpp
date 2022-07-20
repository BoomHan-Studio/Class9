// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "MainGameModeBase.h"

#include "Class9/Main/MapNode.h"
#include "Kismet/GameplayStatics.h"


AMainGameModeBase::AMainGameModeBase()
	:ConsumeUnitVelovity(.2f),
	Real2GameTimeConvertRatio(9.f),
	MapNodesKvp
	{
		{TEXT("C0"), nullptr},
		{TEXT("C1"), nullptr},
		{TEXT("C2"), nullptr},
		{TEXT("C3"), nullptr},
		{TEXT("C4"), nullptr},
		{TEXT("C5"), nullptr},
		{TEXT("C6"), nullptr},
		{TEXT("C7"), nullptr},
		{TEXT("L0"), nullptr},
		{TEXT("L1"), nullptr},
		{TEXT("L2"), nullptr},
		{TEXT("R0"), nullptr},
		{TEXT("R1"), nullptr},
		{TEXT("H0"), nullptr},
		{TEXT("H1"), nullptr},
		//{TEXT("None"), nullptr},
	}
{
	BeginTime = FDateTime(1, 1, 1, 8, 0, 0, 0);
	CourseDuration = FTimespan(0, 40, 0);
	EndTime = FDateTime(1, 1, 1, 8, 40, 0);
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	EndTime = BeginTime + CourseDuration;

	TObjectPtr<UWorld> World = GetWorld();
	MapNodesKvp[TEXT("C0")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("C1")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("C2")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("C3")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("C4")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("C5")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("C6")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("C7")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("L0")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("L1")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("L2")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("R0")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("R1")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("H0")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	MapNodesKvp[TEXT("H1")] = World->SpawnActor<AMapNode>(SubclassOfMapNode);
	
	MapNodesKvp[TEXT("C0")]->NodeName = TEXT("C0");
	MapNodesKvp[TEXT("C1")]->NodeName = TEXT("C1");
	MapNodesKvp[TEXT("C2")]->NodeName = TEXT("C2");
	MapNodesKvp[TEXT("C3")]->NodeName = TEXT("C3");
	MapNodesKvp[TEXT("C4")]->NodeName = TEXT("C4");
	MapNodesKvp[TEXT("C5")]->NodeName = TEXT("C5");
	MapNodesKvp[TEXT("C6")]->NodeName = TEXT("C6");
	MapNodesKvp[TEXT("C7")]->NodeName = TEXT("C7");

	MapNodesKvp[TEXT("L0")]->NodeName = TEXT("L0");
	MapNodesKvp[TEXT("L1")]->NodeName = TEXT("L1");
	MapNodesKvp[TEXT("L2")]->NodeName = TEXT("L2");
	MapNodesKvp[TEXT("R0")]->NodeName = TEXT("R0");
	MapNodesKvp[TEXT("R1")]->NodeName = TEXT("R1");
	MapNodesKvp[TEXT("H0")]->NodeName = TEXT("H0");
	MapNodesKvp[TEXT("H1")]->NodeName = TEXT("H1");
}

void AMainGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

AMapNode* AMainGameModeBase::GetNodeByName(FName InName) const
{
	auto Node = MapNodesKvp.FindRef(InName);
	if (!Node)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("警告：GetNodeByName访问的结点名不存在或该结点名未赋值。"), true, true, FLinearColor::Red, 99.f);
	}
	return Node;
}

FName AMainGameModeBase::GetNameByNode(AMapNode* InNode) const
{
	if (!InNode)
	{
		return TEXT("None");
	}
	auto* NamePtr = MapNodesKvp.FindKey(InNode);
	if (!NamePtr)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("警告：GetNameByNode访问的结点是野结点。"), true, true, FLinearColor::Red, 99.f);
	}
	return *NamePtr;
}
