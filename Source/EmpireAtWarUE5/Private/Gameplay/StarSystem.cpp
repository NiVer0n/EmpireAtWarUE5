// NiVeron Games 2022. All rights reserved.

#include "Gameplay/StarSystem.h"
#include "Components/SphereComponent.h"
#include "Components/SelectionComponent.h"
#include "Components/NameComponent.h"
#include "UI/NameWidget.h"
#include "Utils/SubsystemUtils.h"
#include "Subsystems/FactionsSubsystem.h"

AStarSystem::AStarSystem()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	SelectionComponent = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
	NameComponent = CreateDefaultSubobject<UNameComponent>(TEXT("NameComponent"));
	NameComponent->SetupAttachment(RootComponent);
}

void AStarSystem::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetStaticMesh(StarSystemData->Mesh.Get());
	UNameWidget* NameWidget = CastChecked<UNameWidget>(NameComponent->GetUserWidgetObject());
	NameWidget->SetName(StarSystemData->Name);
	UFactionsSubsystem* FactionsSubsystem = USubsystemUtils::GetFactionsSubsystem(GetWorld());
	FactionsSubsystem->GetGameObjectsFactions().Add(this, StarSystemData->FactionControl);
}

void AStarSystem::SetNameVisibility(bool InVisible)
{
	NameComponent->SetVisibility(InVisible);
}