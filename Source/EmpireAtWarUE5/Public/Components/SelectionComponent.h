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

	UFUNCTION()
	void SetSelectionColor(const FColor SelectionColor);

protected:
	virtual void BeginPlay() override;

	USelectionComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlaneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection Settings")
	UStaticMesh* PlaneMesh;

	UPROPERTY(EditAnywhere, Category = "Selection Settings")
	UMaterialInterface* SelectionMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection Settings")
	USoundCue* SelectedSound;

private:
	UPROPERTY()
	bool bCanBeSelected;

	UPROPERTY()
	bool bIsSelected;

	UPROPERTY()
	bool bHovered;

	UPROPERTY()
	UMaterialInstanceDynamic* SelectionMaterialInstance;
};
