// NiVeron Games 2022. All rights reserved.

#include "Gameplay/StarSystem.h"
#include "Components/SelectionComponent.h"
#include "Components/BoxComponent.h"

AStarSystem::AStarSystem()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AStarSystem::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->SetStaticMesh(StarSystemData->Mesh.Get());
}
