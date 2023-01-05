// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameplayTagContainer.h"
#include "Subsystems/ConsumableResourcesSubsystem.h"
#include "EAWPlayerStateBase.generated.h"

class UFactionComponent;

USTRUCT()
struct FStartupData
{
	GENERATED_BODY()

	FStartupData(){};

	FStartupData(FGameplayTag InFaction, TMap<EResourceTypes, int32> InResources)
		: Faction(InFaction)
		, Resources(InResources)
	{};

	FGameplayTag Faction;

	TMap<EResourceTypes, int32> Resources;
};

/**
 * 
 */
UCLASS()
class EMPIREATWARUE5_API AEAWPlayerStateBase : public APlayerState
{
	GENERATED_BODY()

public:
	FORCEINLINE UFactionComponent* GetFactionComponent() const { return FactionComponent; }

	/* Sets player data on first game start or from save. */
	void ApplyStartupData(FStartupData StartupData);

protected:
	AEAWPlayerStateBase();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFactionComponent* FactionComponent;
};
