// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelectedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeselectedDelegate);

class UMaterialInterface;
class USoundCue;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EMPIREATWARUE5_API USelectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetCanBeSelected(bool CanBeSelected) { bCanBeSelected = CanBeSelected; };
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetCanBeSelected() const { return bCanBeSelected; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsSelected() const { return bSelected; };
	
	UFUNCTION(BlueprintCallable)
	void SelectOwner();

	UFUNCTION(BlueprintCallable)
	void DeselectOwner();

	UPROPERTY(BlueprintAssignable)
	FOnSelectedDelegate OnSelected;

	UPROPERTY(BlueprintAssignable)
	FOnDeselectedDelegate OnDeselected;

protected:
	virtual void BeginPlay() override;
	virtual void DestroyComponent(bool bPromoteChildren) override;

	USelectionComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
	AActor* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
	bool bCanBeSelected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
	bool bSelected;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
	bool bHovered;

	UPROPERTY(EditDefaultsOnly, Category = "Selection Settings")
	UMaterialInterface* SelectionCircleMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Selection Settings")
	UStaticMesh* PlaneMesh;

	UPROPERTY()
	UStaticMeshComponent* PlaneComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Selection Settings")
	USoundCue* SelectedSound;
};
