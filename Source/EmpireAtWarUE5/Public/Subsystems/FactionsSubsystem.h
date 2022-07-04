// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "FactionsSubsystem.generated.h"

UCLASS(meta = (DisplayName = "FactionsSubsystem"))
class EMPIREATWARUE5_API UFactionsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	TMap<APlayerController*, FGameplayTag>& GetPlayerFactions() { return PlayerFactions; }
	TMap<AActor*, FGameplayTag>& GetGameObjectsFactions() { return GameObjectsFactions; }
	FColor GetFactionColor(FGameplayTag Source, FGameplayTag Target) const;

protected:
	UFactionsSubsystem();

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	TMap<APlayerController*, FGameplayTag> PlayerFactions;
	TMap<AActor*, FGameplayTag> GameObjectsFactions;

	UPROPERTY()
	class UDA_Factions* FactionsDataAsset;
};
