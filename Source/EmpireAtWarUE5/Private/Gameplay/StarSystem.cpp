// NiVeron Games 2022. All rights reserved.

#include "Gameplay/StarSystem.h"
#include "Components/SphereComponent.h"
#include "Components/SelectionComponent.h"
#include "Components/FactionComponent.h"
#include "Components/NameComponent.h"
#include "Player/EAWPlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

AStarSystem::AStarSystem()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	SelectionComponent = CreateDefaultSubobject<USelectionComponent>(TEXT("SelectionComponent"));
	NameComponent = CreateDefaultSubobject<UNameComponent>(TEXT("NameComponent"));
	NameComponent->SetupAttachment(RootComponent);

	FactionComponent = CreateDefaultSubobject<UFactionComponent>(TEXT("FactionComponent"));
}

void AStarSystem::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetStaticMesh(StarSystemData->Mesh.Get());
	NameComponent->SetName(StarSystemData->Name);

	FactionComponent->OnFactionControlChanged.AddDynamic(this, &AStarSystem::ChangeFactionControl);
	ChangeFactionControl(StarSystemData->FactionControl);
}

void AStarSystem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	FactionComponent->OnFactionControlChanged.RemoveDynamic(this, &AStarSystem::ChangeFactionControl);
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
	SelectionComponent->SetCanBeSelected(!IsZoomIn);
	SelectionComponent->SetOwnerSelected(!IsZoomIn);
	NameComponent->SetVisibility(!IsZoomIn);
}

void AStarSystem::ChangeFactionControl(FGameplayTag InFactionControlTag)
{
	FactionComponent->SetOwnerFactionTag(InFactionControlTag);
	const AEAWPlayerControllerBase* PC = Cast<AEAWPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	check(PC);
	const FGameplayTag PlayerTag = PC->GetFactionComponent()->GetOwnerFactionTag();

	const FColor SelectionColor = FactionComponent->GetFactionColor(PlayerTag);
	SelectionComponent->SetSelectionCircleColor(SelectionColor);
	NameComponent->SetNameColor(SelectionColor);
}