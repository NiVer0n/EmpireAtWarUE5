// NiVeron Games 2022. All rights reserved.

#include "Data/DA_Factions.h"

FColor UDA_Factions::GetTeamColor(const FGameplayTag TeamTag)
{
	return FactionsData.Contains(TeamTag) ? FactionsData[TeamTag].Color : FColor();
}

bool UDA_Factions::IsNeutral(const FGameplayTag TeamTag)
{
	return TeamTag.MatchesTagExact(NeutralTag);
}

bool UDA_Factions::IsAlly(const FGameplayTag TeamA, const FGameplayTag TeamB)
{
	return TeamA.MatchesTagExact(TeamB) || (FactionsData.Contains(TeamA) && FactionsData[TeamA].Allies.HasTagExact(TeamB));
}

bool UDA_Factions::IsPrimaryEnemies(const FGameplayTag TeamA, const FGameplayTag TeamB)
{
	return !TeamA.MatchesTagExact(TeamB) && FactionsData.Contains(TeamA) && FactionsData[TeamA].PrimaryEnemy.MatchesTagExact(TeamB);
}