// NiVeron Games 2022. All rights reserved.

#include "Components/SelectionComponent.h"
#include "Subsystems/FactionsSubsystem.h"
#include "Utils/SubsystemUtils.h"
#include "Kismet/GameplayStatics.h"

USelectionComponent::USelectionComponent()
	: Owner(nullptr)
	, bCanBeSelected(true)
	, bIsSelected(false)
	, bHovered(false)
{
}

void USelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	checkf(IsValid(Owner), TEXT("USelectionComponent::BeginPlay(): Owner is invalid!"));

	OnSetSelected.AddDynamic(this, &USelectionComponent::SetOwnerSelected);

	ensureMsgf(IsValid(PlaneMesh), TEXT("USelectionComponent::BeginPlay(): PlaneMesh isn't set."));
	PlaneComponent = NewObject<UStaticMeshComponent>(Owner, TEXT("SelectionCirclePlane"));
	PlaneComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PlaneComponent->SetStaticMesh(PlaneMesh);
	PlaneComponent->SetRelativeScale3D(FVector(2.0f));
	SelectionCircleMaterialInstance = UMaterialInstanceDynamic::Create(SelectionCircleMaterial, this);
	PlaneComponent->SetMaterial(0, SelectionCircleMaterialInstance);
	PlaneComponent->SetHiddenInGame(true);
	PlaneComponent->RegisterComponent();
}

void USelectionComponent::SetOwnerSelected(bool bInSelected)
{
	if (bIsSelected == bInSelected)
	{
		return;
	}
	bIsSelected = bInSelected;

	if (IsValid(PlaneComponent))
	{
		PlaneComponent->SetHiddenInGame(!bInSelected);
	}

	UFactionsSubsystem* FactionsSubsystem = USubsystemUtils::GetFactionsSubsystem(GetWorld());
	const FGameplayTag OwnerFactionTag = FactionsSubsystem->GetGameObjectsFactions().FindRef(Owner);
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(PlayerController);
	const FGameplayTag PlayerFactionTag = FactionsSubsystem->GetPlayerFactions().FindRef(PlayerController);
	if (OwnerFactionTag.IsValid() && PlayerFactionTag.IsValid())
	{
		SelectionCircleMaterialInstance->SetVectorParameterValue(TEXT("Color"), FactionsSubsystem->GetFactionColor(PlayerFactionTag, OwnerFactionTag));
	}
}