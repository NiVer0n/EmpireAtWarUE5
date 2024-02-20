// NiVeron Games 2022. All rights reserved.

#include "Components/FactionComponent.h"
#include "Engine/EAWSettings.h"
#include "Data/DA_Factions.h"
#include "Gameplay/EAWGameplayStatics.h"

UFactionComponent::UFactionComponent()
	: FactionTag(FGameplayTag())
	, FactionsDataAsset(nullptr)
{
}

void UFactionComponent::BeginPlay()
{
	Super::BeginPlay();

	FactionsDataAsset = GEAWSettings.GetFactionsDataAsset();
	checkf(FactionsDataAsset, TEXT("%s: FactionsDataAsset is invalid."), ANSI_TO_TCHAR(__FUNCTION__));
}

FColor UFactionComponent::GetOwnerFactionColorForPlayer(int32 PlayerIndex)
{
	if (!GetWorld() || !IsValid(FactionsDataAsset))
	{
		return FColor();
	}

	const FGameplayTag PlayerFactionTag = UEAWGameplayStatics::GetPlayerFactionTag(GetWorld(), PlayerIndex);
	if (FactionsDataAsset->IsPrimaryEnemies(FactionTag, PlayerFactionTag))
	{
		return FactionsDataAsset->GetEnemyColor();
	}
	else if (FactionsDataAsset->IsAlly(FactionTag, PlayerFactionTag))
	{
		return FactionTag.MatchesTagExact(PlayerFactionTag) ? FactionsDataAsset->GetAllyColor() : FactionsDataAsset->GetTeamColor(FactionTag);
	}
	else if (FactionsDataAsset->IsNeutral(FactionTag))
	{
		FactionsDataAsset->GetTeamColor(FactionsDataAsset->GetNeutralTeamTag());
	}
	return FactionsDataAsset->GetTeamColor(FactionTag);
}

void UFactionComponent::SetNewFaction(FGameplayTag NewFactionTag)
{
	FactionTag = NewFactionTag;
	OnFactionChanged.Broadcast(GetOwnerFactionColorForPlayer(0));
}