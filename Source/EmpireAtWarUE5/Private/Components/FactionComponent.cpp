// NiVeron Games 2022. All rights reserved.

#include "Components/FactionComponent.h"
#include "Engine/EAWSettings.h"
#include "Data/DA_Factions.h"
#include "Player/EAWPlayerStateBase.h"
#include "Kismet/GameplayStatics.h"

UFactionComponent::UFactionComponent()
	: FactionsDataAsset(nullptr)
	, TeamID(FGenericTeamId())
{ }

void UFactionComponent::BeginPlay()
{
	Super::BeginPlay();

	FactionsDataAsset = GEAWSettings.GetFactionsDataAsset();
	checkf(FactionsDataAsset, TEXT("%s: FactionsDataAsset is invalid."), ANSI_TO_TCHAR(__FUNCTION__));
}

FColor UFactionComponent::GetFactionColorForPlayer(int32 PlayerIndex)
{
	if (!GetWorld() || !IsValid(FactionsDataAsset))
	{
		return FColor();
	}
	
	const APlayerState* PlayerState = UGameplayStatics::GetPlayerState(GetWorld(), PlayerIndex);
	if (!IsValid(PlayerState))
	{
		return FactionsDataAsset->GetFactionDataForTeamID(FactionsDataAsset->GetTeamIdFromGameplayTag(FactionsDataAsset->GetNeutralTeamTag())).Color;
	}
	
	const ETeamAttitude::Type TeamAttitude = GetTeamAttitudeTowardsActor(PlayerState);
	switch (TeamAttitude)
	{
		case ETeamAttitude::Type::Friendly:
		{
			// Player controlled actors gets ally color otherwise team color.
			const FGenericTeamId ActorTeamId = GetActorTeamId(PlayerState);
			return GetGenericTeamId() == ActorTeamId ? FactionsDataAsset->GetAllyColor() : FactionsDataAsset->GetTeamColor(TeamID);
			break;
		}
		case ETeamAttitude::Type::Hostile:
		{
			// Primary enemies gets enemy color for each other, everyone else receive team color.
			const FGenericTeamId ActorTeamId = GetActorTeamId(PlayerState);
			return FactionsDataAsset->IsPrimaryEnemies(GetGenericTeamId(), ActorTeamId) ? 
				FactionsDataAsset->GetEnemyColor() : FactionsDataAsset->GetTeamColor(TeamID);
			break;
		}
		case ETeamAttitude::Type::Neutral:
		{
			return FactionsDataAsset->GetFactionDataForTeamID(FactionsDataAsset->GetTeamIdFromGameplayTag(FactionsDataAsset->GetNeutralTeamTag())).Color;
			break;
		}
		default: break;
	}
	return FactionsDataAsset->GetFactionDataForTeamID(FactionsDataAsset->GetTeamIdFromGameplayTag(FactionsDataAsset->GetNeutralTeamTag())).Color;
}

ETeamAttitude::Type UFactionComponent::GetTeamAttitudeTowardsActor(const AActor* OtherActor)
{
	return IsValid(OtherActor) ? FGenericTeamId::GetAttitude(GetGenericTeamId(), GetActorTeamId(OtherActor)) : ETeamAttitude::Neutral;
}

void UFactionComponent::SetNewFaction(FGameplayTag NewFactionTag)
{
	check(FactionsDataAsset);
	TeamID = FactionsDataAsset->GetTeamIdFromGameplayTag(NewFactionTag);
	OnFactionControlChanged.Broadcast(GetFactionColorForPlayer(0));
}

FGenericTeamId UFactionComponent::GetActorTeamId(const AActor* InActor) const
{
	check(IsValid(InActor));
	const UFactionComponent* FactionComponent = InActor->FindComponentByClass<UFactionComponent>();
	check(IsValid(FactionComponent));
	return FactionComponent->GetGenericTeamId();
}
