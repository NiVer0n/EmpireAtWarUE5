// NiVeron Games 2022. All rights reserved.

#include "Subsystems/FactionsSubsystem.h"
#include "Data/DA_Factions.h"
#include "Engine/SubsystemsSettings.h"

UFactionsSubsystem::UFactionsSubsystem()
	: PlayerFactions()
	, GameObjectsFactions()
{
}

void UFactionsSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	FactionsDataAsset = GetDefault<USubsystemsSettings>()->GetFactionsDataAsset();
	checkf(IsValid(FactionsDataAsset), TEXT("UFactionsSubsystem::GetFactionColor: FactionsDataAsset is invalid."));
}

FColor UFactionsSubsystem::GetFactionColor(FGameplayTag Source, FGameplayTag Target) const
{
	if (Source.MatchesTagExact(Target))
	{
		return FactionsDataAsset->GetAllyColor();
	}
	const FFactionsData* SourceFactionData = FactionsDataAsset->GetFactionsData().Find(Source);
	if (SourceFactionData && Target.MatchesTagExact(SourceFactionData->PrimaryEnemy))
	{
		return FactionsDataAsset->GetEnemyColor();
	}
	return SourceFactionData->Color;
}