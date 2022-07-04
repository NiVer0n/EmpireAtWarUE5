// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Data/UniverseDataTable.h"
#include "SubsystemsSettings.generated.h"

class AStarSystem;
class UDA_Factions;

/**
 * Class for store default subsystem's settings in Project Settings.
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Subsystems Settings"))
class EMPIREATWARUE5_API USubsystemsSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	FORCEINLINE UDataTable* GetUniverseDataTable() const { return UniverseDataTablePath.LoadSynchronous(); }
	FORCEINLINE TSubclassOf<AStarSystem> GetStarSystemClass() const { return StarSystemClass; }
	FORCEINLINE UDA_Factions* GetFactionsDataAsset() const { return FactionsDataAsset.LoadSynchronous(); }

protected:
	USubsystemsSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "UniverseSubsystem", AdvancedDisplay)
	TSoftObjectPtr<UDataTable> UniverseDataTablePath;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "UniverseSubsystem", AdvancedDisplay)
	TSubclassOf<AStarSystem> StarSystemClass;

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "FactionsSubsystem", AdvancedDisplay)
	TSoftObjectPtr<UDA_Factions> FactionsDataAsset;
};
