// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UniverseSubsystem.generated.h"

/**
 * Generic class for storing and spawning celestial bodies.
 */
UCLASS(meta = (DisplayName = "UniverseSubsystem"))
class EMPIREATWARUE5_API UUniverseSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	UUniverseSubsystem();

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void CreateUniverse();

	UPROPERTY(Transient)
	TMap<FName, AActor*> UniverseMap;
};
