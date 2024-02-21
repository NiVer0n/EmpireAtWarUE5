// NiVeron Games 2023. All rights reserved.

#include "Subsystems/UniverseSubsystem.h"
#include "Data/DA_StarSystem.h"
#include "Data/DA_Universe.h"
#include "Gameplay/StarSystem.h"
#include "Gameplay/TradeRoute.h"
#include "Engine/EAWSettings.h"
#include "Engine.h"
#include "EmpireAtWarUE5/EmpireAtWarUE5.h"

UUniverseSubsystem::UUniverseSubsystem()
	: UniverseMap()
{
	CampaignDataTable = GEAWSettings.GetCampaignDataTable();
}

void UUniverseSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	InWorld.OnWorldMatchStarting.AddUObject(this, &ThisClass::CollectTradeRoutes);
	InWorld.OnWorldMatchStarting.AddUObject(this, &ThisClass::CollectCampaignPlanets);
}

void UUniverseSubsystem::CollectCampaignPlanets()
{
	if (!GetWorld())
		return;

	// Cache CampaignData from DataTable asset
	TMap<FGameplayTag, FCampaignData> CampaignData;
	CampaignDataTable->ForeachRow<FCampaignData>(TEXT("UUniversalDataTable::SetDefaultFactionControl"), [&](const FName& Key, const FCampaignData& Value) {
		CampaignData.Emplace(Value.StarSystemTag, Value);
	});

	for (TActorIterator<AActor> It(GetWorld(), AStarSystem::StaticClass()); It; ++It)
	{
		AStarSystem* StarSystem = Cast<AStarSystem>(*It);
		if (!StarSystem)
		{
			UE_LOG(LogUniverseSubsystem, Warning, TEXT("%s failed to cast to AStarSystem class."), It->GetClass()->GetFName());
			continue;
		}

		const FGameplayTag StarSystemTag = StarSystem->GetStarSystemData()->Tag;
		UniverseMap.Add(StarSystemTag, StarSystem);

		if (StarSystem->Implements<UFactions>())
		{
			const FCampaignData* StarSystemCampaignData = CampaignData.Find(StarSystemTag);
			if (StarSystemCampaignData)
			{
				IFactions::Execute_SetNewFaction(StarSystem, StarSystemCampaignData->DefaultFactionControl);
			}
		}
	}
}

void UUniverseSubsystem::CollectTradeRoutes()
{
	if (!GetWorld()) return;

	for (TActorIterator<AActor> It(GetWorld(), ATradeRoute::StaticClass()); It; ++It)
	{
		ATradeRoute* TradeRoute = Cast<ATradeRoute>(*It);
		if (!TradeRoute)
		{
			UE_LOG(LogUniverseSubsystem, Warning, TEXT("%s failed to cast to ATradeRoute class."), It->GetClass()->GetFName());
			continue;
		}

		TradeRoutes.Add(TradeRoute);
	}
}
