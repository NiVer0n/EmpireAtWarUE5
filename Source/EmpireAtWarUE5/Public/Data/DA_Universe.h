// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DA_Universe.generated.h"

class UDA_StarSystem;

/**
 * Helper data class to store map of star systems data
 */
UCLASS()
class EMPIREATWARUE5_API UDA_Universe : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StarSystemsData", meta = (Categories = "Gameplay.StarSystems"))
	TMap<FGameplayTag, UDA_StarSystem*> StarSystemsData;
};
