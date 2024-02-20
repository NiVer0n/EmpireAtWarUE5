// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameplayTagContainer.h"
#include "Subsystems/ConsumableResourcesSubsystem.h"
#include "Interfaces/Factions.h"
#include "EAWPlayerStateBase.generated.h"

class UFactionComponent;
class AStarSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControlledSystemsChangedDelegate);

USTRUCT()
struct FStartupData
{
	GENERATED_BODY()

	FStartupData(){};

	FStartupData(FGameplayTag InFaction, TMap<EResourceTypes, int32> InResources)
		: Faction(InFaction)
		, Resources(InResources){};

	FGameplayTag Faction;

	TMap<EResourceTypes, int32> Resources;
};

/**
 *
 */
UCLASS()
class EMPIREATWARUE5_API AEAWPlayerStateBase : public APlayerState, public IFactions
{
	GENERATED_BODY()

public:
	FORCEINLINE const TArray<AStarSystem*>& GetControlledStarSystems() { return ControlledStarSystems; }

	void HandleControlledStarSystem(AStarSystem* InStarSystem, bool InControlGained);

	/* Sets player data on first game start or from save. */
	void ApplyStartupData(FStartupData StartupData);

	virtual void SetNewFaction_Implementation(FGameplayTag InNewFactionTag) override;
	virtual FGameplayTag GetFactionTag_Implementation() const override;

	UPROPERTY(BlueprintAssignable, Category = "Gameplay")
	FOnControlledSystemsChangedDelegate OnControlledSystemsChanged;

protected:
	AEAWPlayerStateBase();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFactionComponent* FactionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	TArray<AStarSystem*> ControlledStarSystems;

private:
	UFUNCTION()
	void CollectTaxes(int32 CurrentDay);

	ULocalPlayer* GetLocalPlayer() const;
	void HandleBindings(bool InBinded);
};
