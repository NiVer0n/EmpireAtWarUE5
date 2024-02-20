// NiVeron Games 2022. All rights reserved.

#include "Player/EAWPlayerStateBase.h"
#include "Components/FactionComponent.h"
#include "Utils/EAWGameplayTags.h"
#include "Subsystems/GalaxyTimeSubsystem.h"
#include "Gameplay/StarSystem.h"
#include "Data/DA_StarSystem.h"

AEAWPlayerStateBase::AEAWPlayerStateBase()
	: FactionComponent(nullptr)
	, ControlledStarSystems()
{
	FactionComponent = CreateDefaultSubobject<UFactionComponent>("FactionComponent");
}

void AEAWPlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	TMap<EResourceTypes, int32> StartupResources;
	// @TODO: Rewrite this when implementing faction choise
	StartupResources.Emplace(EResourceTypes::Credits, 5000);
	StartupResources.Emplace(EResourceTypes::Population, 100);
	FStartupData StartupData = FStartupData(GEAWGameplayTags.FACTION_EMPIRE_TAG, StartupResources);
	ApplyStartupData(StartupData);
	HandleBindings(true);
}

void AEAWPlayerStateBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	HandleBindings(false);
	Super::EndPlay(EndPlayReason);
}

void AEAWPlayerStateBase::ApplyStartupData(FStartupData StartupData)
{
	IFactions::Execute_SetNewFaction(this, StartupData.Faction);
	UConsumableResourcesSubsystem* ResourceSubsystem = GetPlayerController()->GetLocalPlayer()->GetSubsystem<UConsumableResourcesSubsystem>();
	for (const auto& [ResourceType, ResourceCount] : StartupData.Resources)
	{
		ResourceSubsystem->AddConsumableResource(ResourceType, ResourceCount);
	}
}

void AEAWPlayerStateBase::SetNewFaction_Implementation(FGameplayTag InNewFactionTag)
{
	FactionComponent->SetNewFaction(InNewFactionTag);
}

FGameplayTag AEAWPlayerStateBase::GetFactionTag_Implementation() const
{
	return FactionComponent->GetFactionTag();
}

void AEAWPlayerStateBase::HandleBindings(bool InBinded)
{
	if (!IsValid(GetLocalPlayer()))
	{
		return;
	}

	UGalaxyTimeSubsystem* GalaxyTimeSubsystem = GetLocalPlayer()->GetWorld()->GetSubsystem<UGalaxyTimeSubsystem>();
	if (InBinded)
	{
		GalaxyTimeSubsystem->OnGalaxyDayChanged.AddUniqueDynamic(this, &ThisClass::CollectTaxes);
	}
	else
	{
		GalaxyTimeSubsystem->OnGalaxyDayChanged.RemoveDynamic(this, &ThisClass::CollectTaxes);
	}
}

void AEAWPlayerStateBase::CollectTaxes(int32 CurrentDay)
{
	if (!IsValid(GetLocalPlayer()))
	{
		return;
	}

	UConsumableResourcesSubsystem* ResourceSubsystem = GetLocalPlayer()->GetSubsystem<UConsumableResourcesSubsystem>();
	for (AStarSystem* StarSystem : ControlledStarSystems)
	{
		if (UDA_StarSystem* Data = StarSystem->GetStarSystemData())
		{
			ResourceSubsystem->AddConsumableResource(EResourceTypes::Credits, Data->TaxAmount);
		}	
	}
}

ULocalPlayer* AEAWPlayerStateBase::GetLocalPlayer() const
{
	return IsValid(GetPlayerController()) ? GetPlayerController()->GetLocalPlayer() : nullptr;
}

void AEAWPlayerStateBase::HandleControlledStarSystem(AStarSystem* InStarSystem, bool InControlGained)
{
	InControlGained ? ControlledStarSystems.Add(InStarSystem) : ControlledStarSystems.Remove(InStarSystem);
	OnControlledSystemsChanged.Broadcast();
}