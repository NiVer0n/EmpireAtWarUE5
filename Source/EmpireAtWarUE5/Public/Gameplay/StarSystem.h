// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Selectable.h"
#include "Interfaces/Zoomable.h"
#include "Interfaces/Factions.h"
#include "StarSystem.generated.h"

class UDA_StarSystem;
class USphereComponent;
class USelectionComponent;
class UNameComponent;
class UFactionComponent;
class UMinimapComponent;

/**
 * Base class of celestial body
 */
UCLASS()
class EMPIREATWARUE5_API AStarSystem : public AActor, public ISelectable, public IZoomable, public IFactions
{
	GENERATED_BODY()

public:
	FORCEINLINE UDA_StarSystem* GetStarSystemData() const { return StarSystemData; }
	void SetStarSystemData(UDA_StarSystem* InStarSystemData);
	
	virtual void SelectObject_Implementation() override;
	virtual void DeselectObject_Implementation() override;
	virtual void ZoomToObject_Implementation(bool IsZoomIn) override;
	virtual void SetNewFaction_Implementation(FGameplayTag InNewFactionTag) override;
	virtual FGameplayTag GetFactionTag_Implementation() const override;
	virtual FColor GetOwnerFactionColor_Implementation(int32 PlayerIndex) const override;

protected:
	AStarSystem();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USelectionComponent* SelectionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNameComponent* NameComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFactionComponent* FactionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMinimapComponent* MinimapComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameplayData")
	UDA_StarSystem* StarSystemData;
};
