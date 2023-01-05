// NiVeron Games 2022. All rights reserved.

#include "Data/DA_Factions.h"

FColor UDA_Factions::GetTeamColor(FGenericTeamId TeamId)
{
	return GetFactionDataForTeamId(TeamId).Color;
}

bool UDA_Factions::IsNeutral(FGenericTeamId TeamId)
{
	const FGameplayTag Tag = GetGameplayTagFromTeamID(TeamId);
	UE_LOG(LogInit, Log, TEXT("FactionTag %s trying to match %s"), *Tag.ToString(), *NeutralTag.ToString());
	return GetGameplayTagFromTeamID(TeamId).MatchesTagExact(NeutralTag);
}

bool UDA_Factions::IsAlly(FGenericTeamId A, FGenericTeamId B)
{
	return A == B || GetFactionDataForTeamId(A).Allies.HasTagExact(GetGameplayTagFromTeamID(B));
}

bool UDA_Factions::IsPrimaryEnemies(FGenericTeamId A, FGenericTeamId B)
{
	return A != B && GetFactionDataForTeamId(A).PrimaryEnemy.MatchesTagExact(GetGameplayTagFromTeamID(B));
}

FGenericTeamId UDA_Factions::GetTeamIdFromGameplayTag(FGameplayTag InGameplayTag)
{
	TArray<FGameplayTag> FactionsKeys;
	FactionsData.GenerateKeyArray(FactionsKeys);
	const FGenericTeamId TeamId = FactionsKeys.Find(InGameplayTag);
	return TeamId != INDEX_NONE ? TeamId : FGenericTeamId::NoTeam;
}

FGameplayTag UDA_Factions::GetGameplayTagFromTeamID(FGenericTeamId TeamId)
{
	TArray<FGameplayTag> FactionsKeys;
	FactionsData.GenerateKeyArray(FactionsKeys);
	check(FactionsKeys.IsValidIndex(uint8(TeamId)));
	return FactionsKeys[uint8(TeamId)];
}

FFactionsData UDA_Factions::GetFactionDataForTeamId(FGenericTeamId TeamId)
{
	TArray<FFactionsData> FactionsValues;
	FactionsData.GenerateValueArray(FactionsValues);
	check(FactionsValues.IsValidIndex(uint8(TeamId)));
	return FactionsValues[uint8(TeamId)];
}
