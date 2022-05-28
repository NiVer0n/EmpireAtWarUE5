// NiVeron Games 2022. All rights reserved.

#include "Gameplay/StarSystem.h"
#include "Components/SphereComponent.h"
#include "Components/SelectionComponent.h"
#include "Components/NameComponent.h"
#include "UI/NameWidget.h"

AStarSystem::AStarSystem()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BoxComponent"));
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
	UNameWidget* NameWidget = Cast<UNameWidget>(NameComponent->GetUserWidgetObject());
	ensure(NameWidget);
	NameWidget->SetName(StarSystemData->Name);
}
