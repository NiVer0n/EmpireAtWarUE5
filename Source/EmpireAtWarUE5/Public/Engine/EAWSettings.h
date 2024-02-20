// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Data/UniverseDataTable.h"
#include "Data/DA_InputConfig.h"
#include "Data/DA_Universe.h"
#include "Gameplay/StarSystem.h"
#include "EAWSettings.generated.h"

class UDA_Factions;

#define GEAWSettings (*UEAWSettings::GetEAWSettings())

/**
 * Class for store default classes and other stuff in Project Settings.
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "EAW Settings"))
class EMPIREATWARUE5_API UEAWSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	FORCEINLINE static const UEAWSettings* GetEAWSettings() { return GetDefault<UEAWSettings>(); }
	FORCEINLINE UDataTable* GetCampaignDataTable() const { return CampaignDataTable.LoadSynchronous(); }
	FORCEINLINE TSubclassOf<AStarSystem> GetStarSystemClass() const { return StarSystemClass.LoadSynchronous(); }
	FORCEINLINE int32 GetGalaxyDayDuration() const { return GalaxyDayDuration; }
	FORCEINLINE float GetGameSpeedMultiplier() const { return GameSpeedMultiplier; }
	FORCEINLINE UDA_Factions* GetFactionsDataAsset() const { return FactionsDataAsset.LoadSynchronous(); }
	FORCEINLINE UDA_InputConfig* GetInputConfigAsset() const { return InputConfigAsset.LoadSynchronous(); }

protected:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "References|Universe")
	TSoftObjectPtr<UDataTable> CampaignDataTable;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "References|Universe")
	TSoftClassPtr<AStarSystem> StarSystemClass;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "GameSettings|Universe", meta = (Units = Seconds))
	int32 GalaxyDayDuration = 0;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "GameSettings|Universe")
	float GameSpeedMultiplier = 2.0f;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "References|Factions")
	TSoftObjectPtr<UDA_Factions> FactionsDataAsset;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "References|Input")
	TSoftObjectPtr<UDA_InputConfig> InputConfigAsset;
};