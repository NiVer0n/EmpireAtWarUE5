// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SubsystemUtils.generated.h"

/**
 * 
 */
UCLASS()
class EMPIREATWARUE5_API USubsystemUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	template <class T>
	static T* GetWorldSubsystem(UWorld* World);
};
