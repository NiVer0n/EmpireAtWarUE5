// NiVeron Games 2022. All rights reserved.

#include "Components/SelectionComponent.h"

USelectionComponent::USelectionComponent()
	: PlaneComponent(nullptr)
	, PlaneMesh(nullptr)
	, SelectionMaterial(nullptr)
	, SelectedSound(nullptr)
	, bCanBeSelected(true)
	, bIsSelected(false)
	, bHovered(false)
	, SelectionMaterialInstance(nullptr)
{
}

void USelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}
	
	ensureMsgf(IsValid(PlaneMesh), TEXT("%s: PlaneMesh isn't set."), ANSI_TO_TCHAR(__FUNCTION__));
	PlaneComponent = NewObject<UStaticMeshComponent>(Owner, TEXT("SelectionCirclePlane"));
	PlaneComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PlaneComponent->SetStaticMesh(PlaneMesh);
	PlaneComponent->SetRelativeScale3D(FVector(2.0f));
	SelectionMaterialInstance = UMaterialInstanceDynamic::Create(SelectionMaterial, this);
	PlaneComponent->SetMaterial(0, SelectionMaterialInstance);
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

void USelectionComponent::SetSelectionColor(const FColor SelectionColor)
{
	SelectionMaterialInstance->SetVectorParameterValue(TEXT("Color"), SelectionColor);
}