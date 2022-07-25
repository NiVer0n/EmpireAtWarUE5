// NiVeron Games 2022. All rights reserved.

#include "Components/FactionComponent.h"
#include "Engine/EAWSettings.h"
#include "Data/DA_Factions.h"

UFactionComponent::UFactionComponent()
	: FactionsDataAsset(nullptr)
	, OwnerFactionTag(FGameplayTag())
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFactionComponent::BeginPlay()
{
	Super::BeginPlay();

	FactionsDataAsset = GetDefault<UEAWSettings>()->GetFactionsDataAsset();
	checkf(FactionsDataAsset, TEXT("%s: FactionsDataAsset is invalid."), ANSI_TO_TCHAR(__FUNCTION__));
}

FColor UFactionComponent::GetFactionColor(FGameplayTag TargetFactionTag) const
{
	if (OwnerFactionTag.MatchesTagExact(TargetFactionTag))
	{
		return FactionsDataAsset->GetAllyColor();
	}

	const FFactionsData* SourceFactionData = FactionsDataAsset->GetFactionsData().Find(OwnerFactionTag);
	if (SourceFactionData && TargetFactionTag.MatchesTagExact(SourceFactionData->PrimaryEnemy))
	{
		return FactionsDataAsset->GetEnemyColor();
	}
	return SourceFactionData->Color;
}