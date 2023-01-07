// NiVeron Games 2022. All rights reserved.

#include "Player/EAWPlayerStateBase.h"
#include "Components/FactionComponent.h"
#include "Utils/EAWGameplayTags.h"

AEAWPlayerStateBase::AEAWPlayerStateBase()
	: FactionComponent(nullptr)
{
	FactionComponent = CreateDefaultSubobject<UFactionComponent>("FactionComponent");
}

void AEAWPlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	TMap<EResourceTypes, int32> StartupResources;
	StartupResources.Emplace(EResourceTypes::Credits, 5000);
	StartupResources.Emplace(EResourceTypes::Population, 100);
	FStartupData StartupData = FStartupData(GEAWGameplayTags.FACTION_EMPIRE_TAG, StartupResources);
	ApplyStartupData(StartupData);
}

void AEAWPlayerStateBase::ApplyStartupData(FStartupData StartupData)
{
	// @TODO: Rewrite this when implementing faction choise
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
