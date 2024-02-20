// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Data/DA_Factions.h"
#include "UniverseDataTable.generated.h"

/**
 * Struct contains gameplay data of singleplayer campaigns
 * e.g. locations (star systems), factions starting forces
 * and other required data.
 */
USTRUCT(BlueprintType)
struct FCampaignData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Gameplay.StarSystems"))
	FGameplayTag StarSystemTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Faction"))
	FGameplayTag DefaultFactionControl;
};

/**
 * Class for determining universe in campaigns
 * e.g. what star systems presented in campaign,
 * default star system control and starting forces
 */
UCLASS()
class EMPIREATWARUE5_API UUniverseDataTable : public UDataTable
{
	GENERATED_BODY()
};
