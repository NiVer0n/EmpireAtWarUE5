// NiVeron Games 2022. All rights reserved.

#include "Gameplay/EAWGameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "Player/EAWPlayerStateBase.h"
#include "Components/FactionComponent.h"

AEAWPlayerStateBase* UEAWGameplayStatics::GetPlayerStateWithFactionTag(const UObject* WorldContextObject, const FGameplayTag InFactionTag)
{
	AGameStateBase* GameState = GetGameState(WorldContextObject);
	if (!IsValid(GameState))
	{
		return nullptr;
	}

	for (APlayerState* Player : GameState->PlayerArray)
	{
		AEAWPlayerStateBase* EAWPlayerState = Cast<AEAWPlayerStateBase>(Player);
		if (!IsValid(EAWPlayerState) || !EAWPlayerState->Implements<UFactions>())
		{
			return nullptr;
		}
		if (IFactions::Execute_GetFactionTag(EAWPlayerState).MatchesTagExact(InFactionTag))
		{
			return EAWPlayerState;
		}
	}
	return nullptr;
}

FGameplayTag UEAWGameplayStatics::GetPlayerFactionTag(const UObject* WorldContextObject, int32 PlayerIndex)
{
	AGameStateBase* GameState = GetGameState(WorldContextObject);
	if (!IsValid(GameState) || !GameState->PlayerArray.IsValidIndex(PlayerIndex))
	{
		return FGameplayTag();
	}

	AEAWPlayerStateBase* EAWPlayerState = Cast<AEAWPlayerStateBase>(GameState->PlayerArray[PlayerIndex]);
	if (IsValid(EAWPlayerState) && EAWPlayerState->Implements<UFactions>())
	{
		return IFactions::Execute_GetFactionTag(EAWPlayerState);
	}
	return FGameplayTag();
}

AGameStateBase* UEAWGameplayStatics::GetGameState(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return IsValid(World) ? World->GetGameState() : nullptr;
}
