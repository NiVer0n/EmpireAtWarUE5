// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UniverseSubsystem.generated.h"

/**
 * Generic class for storing and spawning celestial bodies.
 */
UCLASS(Blueprintable, BlueprintType, abstract, DisplayName = "UniverseSubsystem")
class EMPIREATWARUE5_API UUniverseSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return bShouldBeCreated; }

protected:
	UUniverseSubsystem();

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void CreateUniverse();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Subsystem")
	bool bShouldBeCreated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	class UDataTable* UniverseData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TSubclassOf<class AStarSystem> StarSystemClass;

	UPROPERTY(Transient)
	TMap<FName, AActor*> UniverseMap;
};
