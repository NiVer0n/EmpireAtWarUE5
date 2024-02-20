// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DA_StarSystem.generated.h"

class UMaterialInterface;

/**
 * Class storing gameplay data about star system.
 */
UCLASS()
class EMPIREATWARUE5_API UDA_StarSystem : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Data")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Data")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Visual")
	TSoftObjectPtr<UStaticMesh> OverrideMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Visual")
	TSoftObjectPtr<UMaterialInterface> OverrideMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Visual")
	float OverrideScale;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Visual")
	FVector StarBaseOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Resources")
	int32 CaptureControlBonus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Resources")
	int32 TaxAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Resources")
	int32 AdditionalPopulationAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StarSystemData|Maps")
	FName SpaceTacticalMapName;
};
