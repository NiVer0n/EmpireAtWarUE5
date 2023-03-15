// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "EAWGameplayStatics.generated.h"

class AEAWPlayerStateBase;
class AGameStateBase;

/**
 * 
 */
UCLASS()
class UEAWGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static AEAWPlayerStateBase* GetPlayerStateWithFactionTag(const UObject* WorldContextObject, const FGameplayTag InFactionTag);
	static FGameplayTag GetPlayerFactionTag(const UObject* WorldContextObject, int32 PlayerIndex);
	static AGameStateBase* GetGameState(const UObject* WorldContextObject);
};
