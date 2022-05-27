// NiVeron Games 2022. All rights reserved.

#include "Components/SelectionComponent.h"

USelectionComponent::USelectionComponent()
	: Owner(nullptr)
	, bCanBeSelected(true)
	, bSelected(false)
	, bHovered(false)
{

}

void USelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	checkf(IsValid(Owner), TEXT("USelectionComponent::BeginPlay(): Owner is not valid!"))
	
	OnSelected.AddDynamic(this, &USelectionComponent::SelectOwner);
	OnDeselected.AddDynamic(this, &USelectionComponent::DeselectOwner);
	
	ensureMsgf(IsValid(PlaneMesh), TEXT("USelectionComponent::BeginPlay(): PlaneMesh is not set."));
	PlaneComponent = NewObject<UStaticMeshComponent>(Owner, TEXT("SelectionCirclePlane"));
	PlaneComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PlaneComponent->SetStaticMesh(PlaneMesh);
	PlaneComponent->SetRelativeScale3D(FVector(2.0f));
	UMaterialInstanceDynamic* SelectionCircleMaterialInstance = UMaterialInstanceDynamic::Create(SelectionCircleMaterial, this);
	PlaneComponent->SetMaterial(0, SelectionCircleMaterialInstance);
	PlaneComponent->SetHiddenInGame(true);
	PlaneComponent->RegisterComponent();
}

void USelectionComponent::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);

	if (!IsValid(PlaneComponent)) return;
	PlaneComponent->DestroyComponent();
}

void USelectionComponent::SelectOwner()
{
	if (!bCanBeSelected || bSelected) return;

	bSelected = true;

	if (!IsValid(PlaneComponent)) return;
	PlaneComponent->SetHiddenInGame(false);
}

void USelectionComponent::DeselectOwner()
{
	if (!bSelected) return;

	bSelected = false;

	if (!IsValid(PlaneComponent)) return;
	PlaneComponent->SetHiddenInGame(true);
}