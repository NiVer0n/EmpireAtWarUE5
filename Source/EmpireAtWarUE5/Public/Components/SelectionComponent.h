// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectionComponent.generated.h"

class UMaterialInterface;
class USoundCue;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EMPIREATWARUE5_API USelectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetCanBeSelected(bool bCanSelect) { bCanBeSelected = bCanSelect; }
	FORCEINLINE bool GetCanBeSelected() const { return bCanBeSelected; }
	
	void SetOwnerSelected(bool InSelected);
	void SetSelectionCircleColor(const FColor SelectionColor);

protected:
	virtual void BeginPlay() override;

	USelectionComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
	bool bCanBeSelected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
	bool bIsSelected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
	bool bHovered;

	UPROPERTY(EditAnywhere, Category = "Selection Settings")
	UMaterialInterface* SelectionCircleMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* SelectionCircleMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "Selection Settings")
	UStaticMesh* PlaneMesh;

	UPROPERTY()
	UStaticMeshComponent* PlaneComponent;

	UPROPERTY(EditAnywhere, Category = "Selection Settings")
	USoundCue* SelectedSound;
};
