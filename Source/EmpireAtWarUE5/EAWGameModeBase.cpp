// Copyright Epic Games, Inc. All Rights Reserved.

#include "EAWGameModeBase.h"
#include "Player/EAWPlayerPawnBase.h"
#include "Player/EAWPlayerControllerBase.h"
#include "Player/EAWPlayerStateBase.h"
#include "Player/EAWHUDBase.h"

AEAWGameModeBase::AEAWGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = AEAWPlayerPawnBase::StaticClass();
	PlayerControllerClass = AEAWPlayerControllerBase::StaticClass();
	PlayerStateClass = AEAWPlayerStateBase::StaticClass();
	HUDClass = AEAWHUDBase::StaticClass();
}