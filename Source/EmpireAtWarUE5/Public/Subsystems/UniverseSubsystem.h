// NiVeron Games 2023. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "UniverseSubsystem.generated.h"

class UDataTable;
class UDA_StarSystem;
class AStarSystem;
class ATradeRoute;

/**
 * Class for storing and manipulating all star systems represented in galaxy mode.
 */
UCLASS()
class EMPIREATWARUE5_API UUniverseSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	UUniverseSubsystem();

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void CollectCampaignPlanets();

	void CollectTradeRoutes();

	UPROPERTY()
	TMap<FGameplayTag, AStarSystem*> UniverseMap;

	UPROPERTY()
	TArray<ATradeRoute*> TradeRoutes;

	UPROPERTY()
	UDataTable* CampaignDataTable;

	UPROPERTY()
	TMap<FGameplayTag, UDA_StarSystem*> UniverseData;
};
