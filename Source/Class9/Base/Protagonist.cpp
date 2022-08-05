// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "Protagonist.h"
#include "MainController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AProtagonist::AProtagonist()
	:DirectionCode(2),
	TurningDuration(0.4f),
	Power(0.f),
	MaxPower(100.f),
	OriginalUsage(.75f),
	Usage(.75f),
	UsageRef(&Usage),
	TurningUsageBonus(.5f),
	AimingUsageBonus(.75f),
	LeftPretendingUsageBonus(1.f),
	RightPretendingUsageBonus(1.f),
	PunishmentUsageBonus(2.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);

	PowerHandle = CreateDefaultSubobject<UPlayerPowerHandle>(TEXT("PowerHandle"));
	
}

// Called when the game starts or when spawned
void AProtagonist::BeginPlay()
{
	Super::BeginPlay();

	WhenTurnLeftBegin.AddDynamic(this, &AProtagonist::TurnLeft);
	WhenTurnLeftBegin.AddDynamic(this, &AProtagonist::TurningUsageIncrease);

	WhenTurnLeftEnd.AddDynamic(this, &AProtagonist::TurningUsageRecover);
	
	WhenTurnRightBegin.AddDynamic(this, &AProtagonist::TurnRight);
	WhenTurnRightBegin.AddDynamic(this, &AProtagonist::TurningUsageIncrease);

	WhenTurnRightEnd.AddDynamic(this, &AProtagonist::TurningUsageRecover);
	
	WhenAimBegin.AddDynamic(this, &AProtagonist::AimBegin);
	WhenAimBegin.AddDynamic(this, &AProtagonist::AimingUsageIncrease);
	
	WhenAimEnd.AddDynamic(this, &AProtagonist::AimEnd);
	WhenAimEnd.AddDynamic(this, &AProtagonist::AimingUsageRecover);
	
	WhenLeftPretendBegin.AddDynamic(this, &AProtagonist::LeftPretendBegin);
	WhenLeftPretendBegin.AddDynamic(this, &AProtagonist::LeftPretendingUsageIncrease);
	
	WhenLeftPretendEnd.AddDynamic(this, &AProtagonist::LeftPretendEnd);
	WhenLeftPretendEnd.AddDynamic(this, &AProtagonist::LeftPretendingUsageRecover);
	
	WhenRightPretendBegin.AddDynamic(this, &AProtagonist::RightPretendBegin);
	WhenRightPretendBegin.AddDynamic(this, &AProtagonist::RightPretendingUsageIncrease);
	
	WhenRightPretendEnd.AddDynamic(this, &AProtagonist::RightPretendEnd);
	WhenRightPretendEnd.AddDynamic(this, &AProtagonist::RightPretendingUsageRecover);

	MainController = Cast<AMainController>(GetController());
	World = GetWorld();
	
	TArray<AActor*> Cameras;
	UGameplayStatics::GetAllActorsWithTag(this, TEXT("PlayerCamera"), Cameras);
	ForwardCamera = Cameras[0];
	//UKismetSystemLibrary::PrintString(this, ForwardCamera->GetActorLocation().ToCompactString(), true, false, FLinearColor::Green, 5.f);
	ForwardCamera->SetActorLocation(PlayerCamera->GetComponentToWorld().GetLocation());
	//UKismetSystemLibrary::PrintString(this, ForwardCamera->GetActorLocation().ToCompactString(), true, false, FLinearColor::Green, 5.f);
	LeftCamera = Cameras[1];
	BackwardCamera = Cameras[2];
	RightCamera = Cameras[3];

	CameraList = {BackwardCamera, LeftCamera, ForwardCamera, RightCamera, BackwardCamera};
	DirectionCode = 2;

	Power = MaxPower;
	Usage = OriginalUsage;
}

// Called every frame
void AProtagonist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProtagonist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AProtagonist::BeginDestroy()
{
	Super::BeginDestroy();

	//delete CameraList;
}

#pragma region BASE_IMPLEMENT

void AProtagonist::TurnLeft()
{

	//UKismetSystemLibrary::PrintString(this, TEXT("TurnLeft"), true, false, FLinearColor::Green);
	DirectionCode--;
	MainController->SetViewTargetWithBlend(CameraList[DirectionCode], TurningDuration);

	FTimerHandle Handle;
	World->GetTimerManager().SetTimer(Handle, this, &AProtagonist::TurnLeftEnd, TurningDuration);
}

void AProtagonist::TurnLeftEnd()
{
	WhenTurnLeftEnd.Broadcast();
}

void AProtagonist::TurnRight()
{
	//UKismetSystemLibrary::PrintString(this, TEXT("TurnRight"), true, false, FLinearColor::Green);
	DirectionCode++;
	MainController->SetViewTargetWithBlend(CameraList[DirectionCode], TurningDuration);

	FTimerHandle Handle;
	World->GetTimerManager().SetTimer(Handle, this, &AProtagonist::TurnRightEnd, TurningDuration);
}

void AProtagonist::TurnRightEnd()
{
	WhenTurnRightEnd.Broadcast();
}

void AProtagonist::AimBegin()
{
	//UKismetSystemLibrary::PrintString(this, TEXT("AimBegin"), true, false, FLinearColor::Green);
}

void AProtagonist::AimEnd()
{
	//UKismetSystemLibrary::PrintString(this, TEXT("AimEnd"), true, false, FLinearColor::Red);
}

void AProtagonist::LeftPretendBegin()
{
	//UKismetSystemLibrary::PrintString(this, TEXT("LeftPretendBegin"), true, false, FLinearColor::Green);
}

void AProtagonist::LeftPretendEnd()
{
	//UKismetSystemLibrary::PrintString(this, TEXT("LeftPretendEnd"), true, false, FLinearColor::Red);
}

void AProtagonist::RightPretendBegin()
{
	//UKismetSystemLibrary::PrintString(this, TEXT("RightPretendBegin"), true, false, FLinearColor::Green);
}

void AProtagonist::RightPretendEnd()
{
	//UKismetSystemLibrary::PrintString(this, TEXT("RightPretendEnd"), true, false, FLinearColor::Red);
}

#pragma endregion

float AProtagonist::GetUsage() const
{
	return UsageRef ? *UsageRef : 0.f;
}

void AProtagonist::SetUsage(float Usg)
{
	UsageRef = &Usage;
	Usage = FMath::Clamp(Usage, 0.f, 9999.f);
}

/*EPlayerDirection AProtagonist::GetPlayerDirection() const
{
	return EPlayerDirection(DirectionCode % 4);
}*/
