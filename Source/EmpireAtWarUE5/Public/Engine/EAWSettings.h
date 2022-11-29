// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Data/UniverseDataTable.h"
#include "Data/DA_InputConfig.h"
#include "EAWSettings.generated.h"

class AStarSystem;
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
	FORCEINLINE UDataTable* GetUniverseDataTable() const { return UniverseDataTablePath.LoadSynchronous(); }
	FORCEINLINE TSubclassOf<AStarSystem> GetStarSystemClass() const { return StarSystemClass; }
	FORCEINLINE UDA_Factions* GetFactionsDataAsset() const { return FactionsDataAsset.LoadSynchronous(); }
	FORCEINLINE UDA_InputConfig* GetInputConfigAsset() const { return InputConfigAsset.LoadSynchronous(); }

protected:
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Universe", AdvancedDisplay)
	TSoftObjectPtr<UDataTable> UniverseDataTablePath;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Universe", AdvancedDisplay)
	TSubclassOf<AStarSystem> StarSystemClass;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Factions", AdvancedDisplay)
	TSoftObjectPtr<UDA_Factions> FactionsDataAsset;
	
	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "Input", AdvancedDisplay)
	TSoftObjectPtr<UDA_InputConfig> InputConfigAsset;
};