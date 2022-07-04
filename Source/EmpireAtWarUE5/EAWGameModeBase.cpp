// Copyright Epic Games, Inc. All Rights Reserved.

#include "EAWGameModeBase.h"
#include "Player/EAWPlayerPawnBase.h"
#include "Player/EAWPlayerControllerGalaxy.h"
#include "Subsystems/FactionsSubsystem.h"
#include "Utils/SubsystemUtils.h"
#include "GameplayTagContainer.h"

AEAWGameModeBase::AEAWGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = AEAWPlayerControllerGalaxy::StaticClass();
	DefaultPawnClass = AEAWPlayerPawnBase::StaticClass();
}

void AEAWGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UFactionsSubsystem* FactionsSubsystem = USubsystemUtils::GetFactionsSubsystem(GetWorld());
	FactionsSubsystem->GetPlayerFactions().Add(NewPlayer, FGameplayTag::RequestGameplayTag(TEXT("Factions.Empire")));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("PlayerTag: %s"), *FactionsSubsystem->GetPlayerFactions().Find(NewPlayer)->ToString()));
}