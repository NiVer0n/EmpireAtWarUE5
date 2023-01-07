// Copyright Epic Games, Inc. All Rights Reserved.

#include "EAWGameModeBase.h"
#include "Player/EAWPlayerPawnBase.h"
#include "Player/EAWPlayerControllerBase.h"
#include "Player/EAWPlayerStateBase.h"
#include "Player/EAWHUDBase.h"
#include "Data/UniverseDataTable.h"
#include "Data/DA_StarSystem.h"
#include "Data/DA_Universe.h"
#include "Gameplay/StarSystem.h"
#include "Engine/EAWSettings.h"

AEAWGameModeBase::AEAWGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, UniverseMap()
{
	DefaultPawnClass = AEAWPlayerPawnBase::StaticClass();
	PlayerControllerClass = AEAWPlayerControllerBase::StaticClass();
	PlayerStateClass = AEAWPlayerStateBase::StaticClass();
	HUDClass = AEAWHUDBase::StaticClass();
}

void AEAWGameModeBase::StartPlay()
{
	Super::StartPlay();

	CreateUniverse();
}

void AEAWGameModeBase::CreateUniverse()
{
	const UDataTable* CampaignDataTable = GEAWSettings.GetCampaignDataTable();
	checkf(CampaignDataTable, TEXT("%s: UniverseData is invalid."), ANSI_TO_TCHAR(__FUNCTION__));
	const TSubclassOf<AStarSystem> StarSystemClass = GEAWSettings.GetStarSystemClass();
	checkf(StarSystemClass, TEXT("%s: StarSystemClass is invalid."), ANSI_TO_TCHAR(__FUNCTION__));

	for (const FName& RowName : CampaignDataTable->GetRowNames())
	{
		const FCampaignData* CampaignData = CampaignDataTable->FindRow<FCampaignData>(RowName, FString());
		checkf(CampaignData, TEXT("%s: UniverseData is invalid."), ANSI_TO_TCHAR(__FUNCTION__));

		const TMap<FGameplayTag, UDA_StarSystem*> UniverseData = GEAWSettings.GetUniverseDataAsset()->StarSystemsData;
		UDA_StarSystem* StarSystemData = *UniverseData.Find(CampaignData->StarSystemTag);
		check(StarSystemData);

		AStarSystem* StarSystem = GetWorld()->SpawnActorDeferred<AStarSystem>(StarSystemClass, FTransform(StarSystemData->Position));
		StarSystem->SetStarSystemData(StarSystemData);
		StarSystem->FinishSpawning(FTransform(StarSystemData->Position));
		if (StarSystem->Implements<UFactions>())
		{
			IFactions::Execute_SetNewFaction(StarSystem, CampaignData->DefaultFactionControl);
		}
		UniverseMap.Add(RowName, StarSystem);
	}
}