// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DA_Factions.generated.h"

USTRUCT()
struct FFactionsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "FactionsData")
	FGameplayTag PrimaryEnemy;

	UPROPERTY(EditAnywhere, Category = "FactionsData")
	TArray<FGameplayTag> Allies;

	UPROPERTY(EditAnywhere, Category = "FactionsData")
	TArray<FGameplayTag> Enemies;

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
	FORCEINLINE const TMap<FGameplayTag, FFactionsData>& GetFactionsData() const { return FactionsData; };
	FORCEINLINE FColor GetAllyColor() const { return AllyColor; };
	FORCEINLINE FColor GetEnemyColor() const { return EnemyColor; };

protected:
	UPROPERTY(EditAnywhere, Category = "FactionsData", meta = (Categories = "Faction"))
	TMap<FGameplayTag, FFactionsData> FactionsData;

	UPROPERTY(EditAnywhere, Category = "FactionsData")
	FColor AllyColor;

	UPROPERTY(EditAnywhere, Category = "FactionsData")
	FColor EnemyColor;
};
