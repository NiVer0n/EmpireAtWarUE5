// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/UniverseDataTable.h"
#include "StarSystem.generated.h"

class USelectionComponent;

/**
 * Base class of celestial body
 */
UCLASS()
class EMPIREATWARUE5_API AStarSystem : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetStarSystemData(FStarSystemData* InStarSystemData) { StarSystemData = InStarSystemData; }

	void SetNameVisibility(bool InVisible);
	void SetSelectionVisibility(bool InVisible);
	USelectionComponent* GetSelectionComponent() const { return SelectionComponent; }

protected:
	AStarSystem();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USelectionComponent* SelectionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UNameComponent* NameComponent;

	FStarSystemData* StarSystemData;
};
