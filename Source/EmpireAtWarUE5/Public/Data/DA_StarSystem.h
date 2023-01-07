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
	UPROPERTY(EditAnywhere, Category = "StarSystemData|Data")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, Category = "StarSystemData|Data")
	FText Name;

	UPROPERTY(EditAnywhere, Category = "StarSystemData|Visual")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, Category = "StarSystemData|Visual")
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, Category = "StarSystemData|Visual")
	FVector Position;

	UPROPERTY(EditAnywhere, Category = "StarSystemData|Visual")
	float Scale;
	
	UPROPERTY(EditAnywhere, Category = "StarSystemData|Resources")
	int32 CaptureControlBonus;

	UPROPERTY(EditAnywhere, Category = "StarSystemData|Resources")
	int32 TaxAmount;
	
	UPROPERTY(EditAnywhere, Category = "StarSystemData|Resources")
	int32 AdditionalPopulationAmount;
	
	UPROPERTY(EditAnywhere, Category = "StarSystemData|Maps")
	FName SpaceTacticalMapName;
};
