// Copyright @2021 BoomHan Studio. All Rights Reserved.


#include "MainPlayerState.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AMainPlayerState::AMainPlayerState()
	:StateCode(0u),
	bIsAimKeyPressed(false),
	PowerExternalInfluence(1.f)
{
	
}

void AMainPlayerState::BeginPlay()
{
	Super::BeginPlay();

	Protagonist = Cast<AProtagonist>(GetPawn());
	World = GetWorld();

	Protagonist->WhenAimBeginInvoke.AddDynamic(this, &AMainPlayerState::OnAimKeyPressed);
	Protagonist->WhenAimEndInvoke.AddDynamic(this, &AMainPlayerState::OnAimKeyReleased);

	Protagonist->WhenTurnLeftInvoke.AddDynamic(this, &AMainPlayerState::OnTurnLeftInvoke);
	Protagonist->WhenTurnRightInvoke.AddDynamic(this, &AMainPlayerState::OnTurnRightInvoke);
	Protagonist->WhenAimBeginInvoke.AddDynamic(this, &AMainPlayerState::OnAimBeginInvoke);
	Protagonist->WhenAimEndInvoke.AddDynamic(this, &AMainPlayerState::OnAimEndInvoke);
	Protagonist->WhenLeftPretendBeginInvoke.AddDynamic(this, &AMainPlayerState::OnLeftPretendBeginInvoke);
	Protagonist->WhenLeftPretendEndInvoke.AddDynamic(this, &AMainPlayerState::OnLeftPretendEndInvoke);
	Protagonist->WhenRightPretendBeginInvoke.AddDynamic(this, &AMainPlayerState::OnRightPretendBeginInvoke);
	Protagonist->WhenRightPretendEndInvoke.AddDynamic(this, &AMainPlayerState::OnRightPretendEndInvoke);

	Protagonist->WhenTurnLeftBegin.AddDynamic(this, &AMainPlayerState::SetPlayerTurning);
	Protagonist->WhenTurnRightBegin.AddDynamic(this, &AMainPlayerState::SetPlayerTurning);
	Protagonist->WhenTurnLeftEnd.AddDynamic(this, &AMainPlayerState::ResetPlayerTurning);
	Protagonist->WhenTurnRightEnd.AddDynamic(this, &AMainPlayerState::ResetPlayerTurning);
	Protagonist->WhenAimBegin.AddDynamic(this, &AMainPlayerState::SetPlayerAiming);
	Protagonist->WhenAimEnd.AddDynamic(this, &AMainPlayerState::ResetPlayerAiming);
	Protagonist->WhenLeftPretendBegin.AddDynamic(this, &AMainPlayerState::SetPlayerLeftPretending);
	Protagonist->WhenLeftPretendEnd.AddDynamic(this, &AMainPlayerState::ResetPlayerLeftPretending);
	Protagonist->WhenRightPretendBegin.AddDynamic(this, &AMainPlayerState::SetPlayerRightPretending);
	Protagonist->WhenRightPretendEnd.AddDynamic(this, &AMainPlayerState::ResetPlayerRightPretending);
}

void AMainPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMainPlayerState::SetPlayerTurning()
{
	StateCode |= uint8(EProtagonistState::Turning);
}

void AMainPlayerState::ResetPlayerTurning()
{
	StateCode &= ~uint8(EProtagonistState::Turning);
}

void AMainPlayerState::SetPlayerAiming()
{
	StateCode |= uint8(EProtagonistState::Aiming);
}

void AMainPlayerState::ResetPlayerAiming()
{
	StateCode &= ~uint8(EProtagonistState::Aiming);
}

void AMainPlayerState::SetPlayerLeftPretending()
{
	StateCode |= uint8(EProtagonistState::LeftPretending);
}

void AMainPlayerState::ResetPlayerLeftPretending()
{
	StateCode &= ~uint8(EProtagonistState::LeftPretending);
}

void AMainPlayerState::SetPlayerRightPretending()
{
	StateCode |= uint8(EProtagonistState::RightPretending);
}

void AMainPlayerState::ResetPlayerRightPretending()
{
	StateCode &= ~uint8(EProtagonistState::RightPretending);
}

void AMainPlayerState::SetPlayerPunished()
{
	StateCode |= uint8(EProtagonistState::Punished);
}

void AMainPlayerState::ResetPlayerPunished()
{
	StateCode &= ~uint8(EProtagonistState::Punished);
}

bool AMainPlayerState::IsPlayerIdle() const
{
	return StateCode == uint8(EProtagonistState::Idle);
}

bool AMainPlayerState::IsPlayerTurning() const
{
	return bool(StateCode & uint8(EProtagonistState::Turning));
}

bool AMainPlayerState::IsPlayerAiming() const
{
	return bool(StateCode & uint8(EProtagonistState::Aiming));
}

bool AMainPlayerState::IsPlayerLeftPretending() const
{
	return bool(StateCode & uint8(EProtagonistState::LeftPretending));
}

bool AMainPlayerState::IsPlayerRightPretending() const
{
	return bool(StateCode & uint8(EProtagonistState::RightPretending));
}

bool AMainPlayerState::IsPlayerPretending() const
{
	return bool(StateCode & (uint8(EProtagonistState::RightPretending) | uint8(EProtagonistState::LeftPretending)));
}

bool AMainPlayerState::IsPlayerPunished() const
{
	return bool(StateCode & uint8(EProtagonistState::Punished));
}

EPlayerDirection AMainPlayerState::GetPlayerDirection() const
{
	return EPlayerDirection(Protagonist->DirectionCode % 4);
}

bool AMainPlayerState::CanPlayerEnterIdle() const
{
	return IsPlayerAiming() || IsPlayerTurning();
}

bool AMainPlayerState::CanPlayerEnterTurning() const
{
	return IsPlayerIdle();
}

bool AMainPlayerState::CanPlayerTurnLeft() const
{
	return CanPlayerEnterTurning() && (Protagonist->DirectionCode != 0u);
}

bool AMainPlayerState::CanPlayerTurnRight() const
{
	return CanPlayerEnterTurning() && (Protagonist->DirectionCode != 4u);
}

bool AMainPlayerState::CanPlayerEnterAiming() const
{
	const bool IsLeftPretending = IsPlayerLeftPretending();
	const bool IsRightPretending = IsPlayerRightPretending();
	return IsPlayerIdle() || ((IsLeftPretending && !IsRightPretending) || (IsRightPretending && !IsLeftPretending));
}

bool AMainPlayerState::CanPlayerEnterPretending() const
{
	const bool IsForward = GetPlayerDirection() == EPlayerDirection::Forward;
	return (IsPlayerAiming() || IsPlayerPretending()) && IsForward;
}

void AMainPlayerState::OnTurnLeftInvoke()
{
	const bool Success = CanPlayerTurnLeft();
	if (Success)
	{
		Protagonist->WhenTurnLeftBegin.Broadcast();
	}
}

void AMainPlayerState::OnTurnRightInvoke()
{
	const bool Success = CanPlayerTurnRight();
	if (Success)
	{
		Protagonist->WhenTurnRightBegin.Broadcast();
	}
}

void AMainPlayerState::OnAimBeginInvoke()
{
	const bool Success = CanPlayerEnterAiming();
	if (Success)
	{
		Protagonist->WhenAimBegin.Broadcast();
	}
}

void AMainPlayerState::OnAimEndInvoke()
{
	const bool Success = CanPlayerEnterIdle() && !IsPlayerPretending();
	if (Success)
	{
		Protagonist->WhenAimEnd.Broadcast();
	}
}

void AMainPlayerState::OnLeftPretendBeginInvoke()
{
	const bool Success = CanPlayerEnterPretending();
	if (Success)
	{
		Protagonist->WhenLeftPretendBegin.Broadcast();
	}
}

void AMainPlayerState::OnLeftPretendEndInvoke()
{
	const bool Success = IsPlayerLeftPretending();
	if (Success)
	{
		Protagonist->WhenLeftPretendEnd.Broadcast();
		if ((!IsPlayerPretending()) && (!bIsAimKeyPressed))
		{
			OnAimEndInvoke();
		}
	}
}

void AMainPlayerState::OnRightPretendBeginInvoke()
{
	const bool Success = CanPlayerEnterPretending();
	if (Success)
	{
		Protagonist->WhenRightPretendBegin.Broadcast();
	}
}

void AMainPlayerState::OnRightPretendEndInvoke()
{
	const bool Success = IsPlayerRightPretending();
	if (Success)
	{
		Protagonist->WhenRightPretendEnd.Broadcast();
		if ((!IsPlayerPretending()) && (!bIsAimKeyPressed))
		{
			OnAimEndInvoke();
		}
	}
}

void AMainPlayerState::RefreshPEI()
{
	PowerExternalInfluence = 1.f;
	for (const auto& Pair : PEISet)
	{
		PowerExternalInfluence *= Pair.Value;
	}
}

void AMainPlayerState::UpdatePEI(float Ratio)
{
	PowerExternalInfluence *= Ratio;
}

void AMainPlayerState::UpdatePEI2(float OldRatio, float NewRatio)
{
	PowerExternalInfluence *= NewRatio / OldRatio;
}

FName Cat(UObject* Caller, FName InName)
{
	return FName(Caller->GetName() + TEXT("-") + InName.ToString());
	//return FName(FString::Printf(TEXT("%s-%s"), Caller->GetName(), InName));
}

void AMainPlayerState::UpdateInfluence(UObject* Caller, FName InName, float Ratio)
{
	FName FullName = Cat(Caller, InName);
	auto* RPtr = PEISet.Find(FullName);
	if (RPtr)
	{
		UpdatePEI2(*RPtr, Ratio);
		*RPtr = Ratio;
	}
	else
	{
		UpdatePEI(Ratio);
		PEISet.Add(FullName, Ratio);
	}
	
}

void AMainPlayerState::RemoveInfluence(UObject* Caller, FName InName)
{
	FName FullName = Cat(Caller, InName);
	auto* RPtr = PEISet.Find(FullName);
	if (!RPtr)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("警告，某对象输入了一个不存在的名字：") + FullName.ToString(), true, true, FLinearColor::Red, 99.f);
		return;
	}
	float Ratio = PEISet.FindAndRemoveChecked(FullName);
	if (FMath::IsNearlyZero(Ratio))
	{
		RefreshPEI();
	}
	else
	{
		UpdatePEI(1.f / Ratio);
	}
}
