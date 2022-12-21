// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EAWGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EMPIREATWARUE5_API AEAWGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	AEAWGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	void CreateUniverse();

	UPROPERTY(Transient)
	TMap<FName, AActor*> UniverseMap;
};
