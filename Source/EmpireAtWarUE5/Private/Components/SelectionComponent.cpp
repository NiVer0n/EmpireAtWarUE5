// NiVeron Games 2022. All rights reserved.

#include "Components/SelectionComponent.h"

USelectionComponent::USelectionComponent()
	: bCanBeSelected(true)
	, bHovered(false)
{
}

void USelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	checkf(IsValid(Owner), TEXT("USelectionComponent::BeginPlay(): Owner is invalid!"));

	ensureMsgf(IsValid(PlaneMesh), TEXT("USelectionComponent::BeginPlay(): PlaneMesh isn't set."));
	PlaneComponent = NewObject<UStaticMeshComponent>(Owner, TEXT("SelectionCirclePlane"));
	PlaneComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PlaneComponent->SetStaticMesh(PlaneMesh);
	PlaneComponent->SetRelativeScale3D(FVector(2.0f));
	SelectionCircleMaterialInstance = UMaterialInstanceDynamic::Create(SelectionCircleMaterial, this);
	PlaneComponent->SetMaterial(0, SelectionCircleMaterialInstance);
	PlaneComponent->SetVisibility(false);
	PlaneComponent->RegisterComponent();
}

void USelectionComponent::SetOwnerSelected(bool InSelected)
{
	if (bCanBeSelected)
	{
		PlaneComponent->SetVisibility(InSelected);
	}
}

void USelectionComponent::SetSelectionCircleColor(const FColor SelectionColor)
{
	SelectionCircleMaterialInstance->SetVectorParameterValue(TEXT("Color"), SelectionColor);
}