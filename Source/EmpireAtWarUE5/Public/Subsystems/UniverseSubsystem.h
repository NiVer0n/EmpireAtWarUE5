// NiVeron Games 2023. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "UniverseSubsystem.generated.h"

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

private:
	void InitializeCampaignPlanetsList();

	UPROPERTY()
	TMap<FGameplayTag, class AStarSystem*> UniverseMap;

	UPROPERTY()
	class UDataTable* CampaignDataTable;

	UPROPERTY()
	TSubclassOf<AStarSystem> StarSystemClass;

	UPROPERTY()
	TMap<FGameplayTag, class UDA_StarSystem*> UniverseData;
};
