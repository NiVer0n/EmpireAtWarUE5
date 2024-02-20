// NiVeron Games 2022. All rights reserved.

#include "Gameplay/StarSystem.h"
#include "Components/SphereComponent.h"
#include "Components/SelectionComponent.h"
#include "Components/FactionComponent.h"
#include "Components/NameComponent.h"
#include "Components/MinimapComponent.h"
#include "Components/StarbaseComponent.h"
#include "Data/DA_StarSystem.h"
#include "Player/EAWPlayerStateBase.h"
#include "Gameplay/EAWGameplayStatics.h"
#include "EmpireAtWarUE5/EmpireAtWarUE5.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

AStarSystem::AStarSystem()
	: SphereComponent(nullptr)
	, MeshComponent(nullptr)
	, SelectionComponent(nullptr)
	, NameComponent(nullptr)
	, FactionComponent(nullptr)
	, MinimapComponent(nullptr)
	, StarbaseComponent(nullptr)
	, StarSystemData()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(RootComponent);

	FactionComponent = CreateDefaultSubobject<UFactionComponent>("FactionComponent");
	MinimapComponent = CreateDefaultSubobject<UMinimapComponent>("MinimapComponent");
	SelectionComponent = CreateDefaultSubobject<USelectionComponent>("SelectionComponent");
	NameComponent = CreateDefaultSubobject<UNameComponent>("NameComponent");
	NameComponent->SetupAttachment(RootComponent);
	
	StarbaseComponent = CreateDefaultSubobject<UStarbaseComponent>("StarbaseComponent");
	StarbaseComponent->SetupAttachment(RootComponent);
}

void AStarSystem::BeginPlay()
{
	Super::BeginPlay();

	InitializeStarSystem();

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

void AStarSystem::InitializeStarSystem()
{
	if (!IsValid(StarSystemData))
	{
		UE_LOG(LogStarSystem, Error, TEXT("Missing StarSystemData in %s"), GetClass()->GetFName());
		return;
	}
	
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	// Override default visual of starsystem
	if (MeshComponent)
	{
		Streamable.RequestAsyncLoad(StarSystemData->OverrideMesh.ToSoftObjectPath(), [this] 
		{
			MeshComponent->SetStaticMesh(StarSystemData->OverrideMesh.Get());
		});

		Streamable.RequestAsyncLoad(StarSystemData->OverrideMaterial.ToSoftObjectPath(), [this] {
			MeshComponent->SetMaterial(0, StarSystemData->OverrideMaterial.Get());
		});

		if (StarSystemData->OverrideScale > 0.0)
		{
			MeshComponent->SetRelativeScale3D(FVector(StarSystemData->OverrideScale));
		}
	}

	if (NameComponent)
	{
		NameComponent->SetName(StarSystemData->Name);
	}

	if (StarbaseComponent)
	{
		StarbaseComponent->SetRelativeLocation(StarSystemData->StarBaseOffset);
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