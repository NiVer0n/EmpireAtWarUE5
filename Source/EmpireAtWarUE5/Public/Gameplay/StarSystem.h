// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/UniverseDataTable.h"
#include "StarSystem.generated.h"

/**
 * Base class of celestial body
 */
UCLASS()
class EMPIREATWARUE5_API AStarSystem : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetStarSystemData(FStarSystemData* InStarSystemData) { StarSystemData = InStarSystemData; }

protected:
	AStarSystem();

	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	FStarSystemData* StarSystemData;

	UPROPERTY(Transient)
	class USelectionComponent* SelectionComponent;
};
