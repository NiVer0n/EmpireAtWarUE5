// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "Factions.generated.h"

UINTERFACE(MinimalAPI)
class UFactions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EMPIREATWARUE5_API IFactions
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Faction")
	void SetNewFaction(FGameplayTag InNewFaction);
	virtual void SetNewFaction_Implementation(FGameplayTag InNewFactionTag) {};
};
