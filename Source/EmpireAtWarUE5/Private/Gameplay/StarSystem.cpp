// NiVeron Games 2022. All rights reserved.

#include "Gameplay/StarSystem.h"
#include "Components/SphereComponent.h"
#include "Components/SelectionComponent.h"
#include "Components/FactionComponent.h"
#include "Components/NameComponent.h"
#include "Components/MinimapComponent.h"
#include "Data/DA_StarSystem.h"
#include "Player/EAWPlayerStateBase.h"
#include "Gameplay/EAWGameplayStatics.h"

AStarSystem::AStarSystem()
	: SphereComponent(nullptr)
	, MeshComponent(nullptr)
	, SelectionComponent(nullptr)
	, NameComponent(nullptr)
	, FactionComponent(nullptr)
	, MinimapComponent(nullptr)
	, StarSystemData()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	FactionComponent = CreateDefaultSubobject<UFactionComponent>(TEXT("FactionComponent"));
	MinimapComponent = CreateDefaultSubobject<UMinimapComponent>(TEXT("MinimapComponent"));
	SelectionComponent = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
	NameComponent = CreateDefaultSubobject<UNameComponent>(TEXT("NameComponent"));
	NameComponent->SetupAttachment(RootComponent);
}

void AStarSystem::BeginPlay()
{
	Super::BeginPlay();

	FactionComponent->OnFactionChanged.AddUniqueDynamic(SelectionComponent, &USelectionComponent::SetSelectionColor);
	FactionComponent->OnFactionChanged.AddUniqueDynamic(MinimapComponent, &UMinimapComponent::ReloadMinimapIcon);
	FactionComponent->OnFactionChanged.AddUniqueDynamic(NameComponent, &UNameComponent::SetNameColor);
}

void AStarSystem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	FactionComponent->OnFactionChanged.RemoveDynamic(SelectionComponent, &USelectionComponent::SetSelectionColor);
	FactionComponent->OnFactionChanged.RemoveDynamic(MinimapComponent, &UMinimapComponent::ReloadMinimapIcon);
	FactionComponent->OnFactionChanged.RemoveDynamic(NameComponent, &UNameComponent::SetNameColor);
	
	Super::EndPlay(EndPlayReason);
}

void AStarSystem::SetStarSystemData(UDA_StarSystem* InStarSystemData)
{
	StarSystemData = InStarSystemData;

	if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(StarSystemData->Mesh.Get());
	}

	if (NameComponent)
	{
		NameComponent->SetName(StarSystemData->Name);
	}
}

void AStarSystem::SelectObject_Implementation()
{
	SelectionComponent->SetOwnerSelected(true);
}

void AStarSystem::DeselectObject_Implementation()
{
	SelectionComponent->SetOwnerSelected(false);
}

void AStarSystem::ZoomToObject_Implementation(bool IsZoomIn)
{
	SelectionComponent->SetOwnerSelected(!IsZoomIn);
	SelectionComponent->SetCanBeSelected(!IsZoomIn);
	NameComponent->SetVisibility(!IsZoomIn);
}

void AStarSystem::SetNewFaction_Implementation(FGameplayTag InNewFactionTag)
{
	if (!GetWorld())
	{
		return;
	}

	AEAWPlayerStateBase* OwningPlayerState = UEAWGameplayStatics::GetPlayerStateWithFactionTag(GetWorld(), FactionComponent->GetFactionTag());
	if (IsValid(OwningPlayerState))
	{
		OwningPlayerState->HandleControlledStarSystem(this, false);
	}

	FactionComponent->SetNewFaction(InNewFactionTag);
	OwningPlayerState = UEAWGameplayStatics::GetPlayerStateWithFactionTag(GetWorld(), InNewFactionTag);
	if (IsValid(OwningPlayerState))
	{
		OwningPlayerState->HandleControlledStarSystem(this, true);
	}
}

FGameplayTag AStarSystem::GetFactionTag_Implementation() const
{
	return FactionComponent->GetFactionTag();
}

FColor AStarSystem::GetOwnerFactionColor_Implementation(int32 PlayerIndex) const
{
	return FactionComponent->GetOwnerFactionColorForPlayer(PlayerIndex);
}