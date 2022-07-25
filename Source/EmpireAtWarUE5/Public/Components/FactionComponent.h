// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "FactionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFactionControlChanged, FGameplayTag, NewFactionControlTag);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EMPIREATWARUE5_API UFactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FGameplayTag GetOwnerFactionTag() const { return OwnerFactionTag; }
	void SetOwnerFactionTag(FGameplayTag NewFactionTag) { OwnerFactionTag = NewFactionTag; }
	FColor GetFactionColor(FGameplayTag TargetFactionTag) const;

	UPROPERTY(BlueprintAssignable)
	FOnFactionControlChanged OnFactionControlChanged;

protected:
	UFactionComponent();

	virtual void BeginPlay() override;

	UPROPERTY()
	class UDA_Factions* FactionsDataAsset;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Factions")
	FGameplayTag OwnerFactionTag;
};
