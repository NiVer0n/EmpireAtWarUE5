// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "FactionComponent.generated.h"

class UDA_Factions;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFactionChangedDelegate, FColor, NewFactionControlColor);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EMPIREATWARUE5_API UFactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Team Affiliation")
	FColor GetOwnerFactionColorForPlayer(int32 PlayerIndex);

	UFUNCTION(BlueprintCallable, Category = "Team Affiliation")
	void SetNewFaction(FGameplayTag NewFactionTag);

	UFUNCTION(BlueprintCallable, Category = "Team Affiliation")
	FORCEINLINE FGameplayTag GetFactionTag() const { return FactionTag; }
	
	UPROPERTY(BlueprintAssignable, Category = "Team Affiliation")
	FOnFactionChangedDelegate OnFactionChanged;

protected:
	UFactionComponent();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Team Affiliation")
	FGameplayTag FactionTag;

private:
	UPROPERTY()
	UDA_Factions* FactionsDataAsset;
};
