// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "Enemy.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
	:NodesMap(
{{TEXT("C0"), FEnemyPropertiesNode()}, {TEXT("C1"), FEnemyPropertiesNode()}, {TEXT("C2"), FEnemyPropertiesNode()},
{TEXT("C3"), FEnemyPropertiesNode()}, {TEXT("C4"), FEnemyPropertiesNode()}, {TEXT("C5"), FEnemyPropertiesNode()},
{TEXT("C6"), FEnemyPropertiesNode()}, {TEXT("C7"), FEnemyPropertiesNode()}, {TEXT("L0"), FEnemyPropertiesNode()},
{TEXT("L1"), FEnemyPropertiesNode()}, {TEXT("L2"), FEnemyPropertiesNode()}, {TEXT("R0"), FEnemyPropertiesNode()},
{TEXT("R1"), FEnemyPropertiesNode()}, {TEXT("H0"), FEnemyPropertiesNode()}, {TEXT("H1"), FEnemyPropertiesNode()},
	})
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	GameModeBase = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	/*WhenEnterC0.AddDynamic(this, &AEnemy::OnEnterC0);
	WhenEnterC1.AddDynamic(this, &AEnemy::OnEnterC1);
	WhenEnterC2.AddDynamic(this, &AEnemy::OnEnterC2);
	WhenEnterC3.AddDynamic(this, &AEnemy::OnEnterC3);
	WhenEnterC4.AddDynamic(this, &AEnemy::OnEnterC4);
	WhenEnterC5.AddDynamic(this, &AEnemy::OnEnterC5);
	WhenEnterC6.AddDynamic(this, &AEnemy::OnEnterC6);
	WhenEnterC7.AddDynamic(this, &AEnemy::OnEnterC7);
	
	WhenEnterL0.AddDynamic(this, &AEnemy::OnEnterL0);
	WhenEnterL1.AddDynamic(this, &AEnemy::OnEnterL1);
	WhenEnterL2.AddDynamic(this, &AEnemy::OnEnterL2);
	
	WhenEnterR0.AddDynamic(this, &AEnemy::OnEnterR0);
	WhenEnterR1.AddDynamic(this, &AEnemy::OnEnterR1);
	
	WhenEnterH0.AddDynamic(this, &AEnemy::OnEnterH0);
	WhenEnterH1.AddDynamic(this, &AEnemy::OnEnterH1);*/
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::OnMove_Implementation(AMapNode* From, AMapNode* To)
{
	if (!To)
	{
		OnRemove(From);
	}
}

void AEnemy::OnRemove(AMapNode* From)
{
	From->RemoveEnemy(this);
}

/*void AEnemy::OnEnterC0_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterC1_Implementation(AMapNode* From)
{
	if (From->GetNodeName() == TEXT("L0"))
	{
		
	}
}

void AEnemy::OnEnterC2_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterC3_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterC4_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterC5_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterC6_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterC7_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterL0_Implementation(AMapNode* From)
{
	if (From->GetNodeName() == TEXT("C1"))
	{
		
	}
}

void AEnemy::OnEnterL1_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterL2_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterR0_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterR1_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterH0_Implementation(AMapNode* From)
{
	
}

void AEnemy::OnEnterH1_Implementation(AMapNode* From)
{
	
}*/