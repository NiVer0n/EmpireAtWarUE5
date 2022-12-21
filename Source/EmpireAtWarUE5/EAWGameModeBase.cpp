// Copyright Epic Games, Inc. All Rights Reserved.

#include "EAWGameModeBase.h"
#include "Player/EAWPlayerPawnBase.h"
#include "Player/EAWPlayerControllerGalaxy.h"
#include "Player/EAWHUDBase.h"
#include "Data/UniverseDataTable.h"
#include "Gameplay/StarSystem.h"
#include "Engine/EAWSettings.h"

AEAWGameModeBase::AEAWGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, UniverseMap()
{
	PlayerControllerClass = AEAWPlayerControllerGalaxy::StaticClass();
	DefaultPawnClass = AEAWPlayerPawnBase::StaticClass();
	HUDClass = AEAWHUDBase::StaticClass();
}

void AEAWGameModeBase::StartPlay()
{
	Super::StartPlay();

	CreateUniverse();
}

void AEAWGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AEAWPlayerControllerBase* PC = Cast<AEAWPlayerControllerBase>(NewPlayer);
	check(PC);
	PC->ApplyStartupData();
}

void AEAWGameModeBase::CreateUniverse()
{
	const UDataTable* UniverseData = GEAWSettings.GetUniverseDataTable();
	checkf(UniverseData, TEXT("%s: UniverseData is invalid."), ANSI_TO_TCHAR(__FUNCTION__));

	const TSubclassOf<AStarSystem> StarSystemClass = GEAWSettings.GetStarSystemClass();
	checkf(StarSystemClass, TEXT("%s: StarSystemClass is invalid."), ANSI_TO_TCHAR(__FUNCTION__));

	for (FName& RowName : UniverseData->GetRowNames())
	{
		if (FStarSystemData* Data = UniverseData->FindRow<FStarSystemData>(RowName, FString()))
		{
			AStarSystem* CelestialBody = GetWorld()->SpawnActorDeferred<AStarSystem>(StarSystemClass, FTransform(Data->Position), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			CelestialBody->SetStarSystemData(Data);
			CelestialBody->FinishSpawning(FTransform(Data->Position));
			UniverseMap.Add(RowName, CelestialBody);
		}
	}
}