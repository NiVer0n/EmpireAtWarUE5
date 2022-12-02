// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Data/DA_Factions.h"
#include "UniverseDataTable.generated.h"

USTRUCT(BlueprintType)
struct FStarSystemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Faction"))
	FGameplayTag FactionControl;
};

/**
 * Class for storing data about celestial bodies (a.k.a starsystems)
 */
UCLASS()
class EMPIREATWARUE5_API UUniverseDataTable : public UDataTable
{
	GENERATED_BODY()
};
