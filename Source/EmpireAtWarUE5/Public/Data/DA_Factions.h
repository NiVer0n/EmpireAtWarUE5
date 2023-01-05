// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "DA_Factions.generated.h"

USTRUCT()
struct FFactionsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "FactionsData", meta = (Categories = "Faction"))
	FGameplayTag PrimaryEnemy;

	UPROPERTY(EditAnywhere, Category = "FactionsData", meta = (Categories = "Faction"))
	FGameplayTagContainer Allies;

	UPROPERTY(EditAnywhere, Category = "FactionsData", meta = (Categories = "Faction"))
	FGameplayTagContainer Enemies;

	UPROPERTY(EditAnywhere, Category = "FactionsData")
	FColor Color;
};

/**
 * 
 */
UCLASS()
class EMPIREATWARUE5_API UDA_Factions : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE FColor GetAllyColor() const { return AllyColor; };
	FORCEINLINE FColor GetEnemyColor() const { return EnemyColor; };
	FORCEINLINE FGameplayTag GetNeutralTeamTag() const { return NeutralTag; }
	FColor GetTeamColor(FGenericTeamId TeamId);
	bool IsNeutral(FGenericTeamId TeamId);
	bool IsAlly(FGenericTeamId A, FGenericTeamId B);
	bool IsPrimaryEnemies(FGenericTeamId A, FGenericTeamId B);

protected:
	UPROPERTY(EditAnywhere, Category = "FactionsData", meta = (Categories = "Faction"))
	TMap<FGameplayTag, FFactionsData> FactionsData;

	/* Team color for player team in singleplayer game. */
	UPROPERTY(EditAnywhere, Category = "FactionsData")
	FColor AllyColor;

	/* Team color for primary enemies in singleplayer game. */
	UPROPERTY(EditAnywhere, Category = "FactionsData")
	FColor EnemyColor;

	/* Tag to detect neutral Team. */
	UPROPERTY(EditAnywhere, Category = "FactionsData", meta = (Categories = "Faction"))
	FGameplayTag NeutralTag;

private:
	FGenericTeamId GetTeamIdFromGameplayTag(FGameplayTag InGameplayTag);
	FGameplayTag GetGameplayTagFromTeamID(FGenericTeamId TeamId);
	FFactionsData GetFactionDataForTeamId(FGenericTeamId TeamId);

	friend class UFactionComponent;
};
