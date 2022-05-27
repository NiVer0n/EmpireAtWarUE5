// Copyright Epic Games, Inc. All Rights Reserved.

#include "EAWGameModeBase.h"
#include "Player/EAWPlayerPawnBase.h"
#include "Player/EAWPlayerControllerGalaxy.h"

AEAWGameModeBase::AEAWGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = AEAWPlayerControllerGalaxy::StaticClass();
	DefaultPawnClass = AEAWPlayerPawnBase::StaticClass();
}