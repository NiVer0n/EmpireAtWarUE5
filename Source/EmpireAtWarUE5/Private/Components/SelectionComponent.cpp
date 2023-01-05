// NiVeron Games 2022. All rights reserved.

#include "Components/SelectionComponent.h"
#include "Components/FactionComponent.h"

USelectionComponent::USelectionComponent()
	: bCanBeSelected(true)
	, bHovered(false)
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
	SelectionCircleMaterialInstance = UMaterialInstanceDynamic::Create(SelectionCircleMaterial, this);
	PlaneComponent->SetMaterial(0, SelectionCircleMaterialInstance);
	PlaneComponent->SetVisibility(false);
	PlaneComponent->RegisterComponent();

	FactionComponent = Owner->FindComponentByClass<UFactionComponent>();
	if (IsValid(FactionComponent))
	{
		FactionComponent->OnFactionControlChanged.AddDynamic(this, &USelectionComponent::ReloadSelectionColor);
	}
}

void USelectionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(FactionComponent))
	{
		FactionComponent->OnFactionControlChanged.RemoveDynamic(this, &USelectionComponent::ReloadSelectionColor);
	}

	Super::EndPlay(EndPlayReason);
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

void USelectionComponent::ReloadSelectionColor()
{
	if (IsValid(FactionComponent))
	{
		SetSelectionCircleColor(FactionComponent->GetFactionColorForPlayer(0));
	}
}