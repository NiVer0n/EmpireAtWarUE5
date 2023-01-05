// NiVeron Games 2022. All rights reserved.

#include "Gameplay/StarSystem.h"
#include "Components/SphereComponent.h"
#include "Components/SelectionComponent.h"
#include "Components/FactionComponent.h"
#include "Components/NameComponent.h"
#include "Components/MinimapComponent.h"

AStarSystem::AStarSystem()
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

	MeshComponent->SetStaticMesh(StarSystemData->Mesh.Get());
	NameComponent->SetName(StarSystemData->Name);

	FactionComponent->SetNewFaction(StarSystemData->FactionControl);
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