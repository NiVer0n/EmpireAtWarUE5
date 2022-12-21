// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ConsumableResourcesSubsystem.generated.h"

/*
 * All resource types available in the game are listed here.
 */
UENUM(BlueprintType)
enum class EResourceTypes : uint8
{
	/* Non-type resource. Default value. */
	None,
	/* Required for ships/base production. */
	Credits,
	/* How many ship can player have at the same time. */
	Population
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourcesChanged, const EResourceTypes, ResourceType, int32, Amount);

/**
 * Class managing player resources, e.g. add/consume resources for certain gameplay actions.
 */
UCLASS()
class UConsumableResourcesSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	/* Returns true if adding succeded. */
	UFUNCTION(BlueprintCallable)
	void AddConsumableResource(const EResourceTypes ResourceType, int32 Amount);

	/* Returns true if consume succeded. */
	UFUNCTION(BlueprintCallable)
	bool ConsumeResource(const EResourceTypes ResourceType, int32 Amount);

	/* Delegate used to update values in UI. */
	UPROPERTY(BlueprintAssignable)
	FOnResourcesChanged OnResourcesChanged;

	/* Map that contains all available resources for player. */
	UPROPERTY(VisibleAnywhere, Category = "ConsumableResources")
	TMap<EResourceTypes, int32> ConsumableResources;
};
