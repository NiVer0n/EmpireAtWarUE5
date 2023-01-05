// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "FactionComponent.generated.h"

class UDA_Factions;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFactionControlChanged);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EMPIREATWARUE5_API UFactionComponent : public UActorComponent, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Team Affiliation")
	FColor GetFactionColorForPlayer(int32 PlayerIndex);

	UFUNCTION(BlueprintCallable, Category = "Team Affiliation")
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override { TeamID = NewTeamID; }

	UFUNCTION(BlueprintCallable, Category = "Team Affiliation")
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }

	UFUNCTION(BlueprintCallable, Category = "Team Affiliation")
	ETeamAttitude::Type GetTeamAttitudeTowardsActor(const AActor* OtherActor);
	// TODO: remove this after implementing faction select
	UFUNCTION(BlueprintCallable, Category = "Team Affiliation")
	void SetNewFaction(FGameplayTag NewFactionTag);

	UPROPERTY(BlueprintAssignable, Category = "Team Affiliation")
	FOnFactionControlChanged OnFactionControlChanged;

protected:
	UFactionComponent();

	virtual void BeginPlay() override;

	UPROPERTY(Transient)
	UDA_Factions* FactionsDataAsset;

	UPROPERTY(VisibleAnywhere, Category = "Team Affiliation")
	FGenericTeamId TeamID;

private:
	FGenericTeamId GetActorTeamId(const AActor* InActor) const;
};
