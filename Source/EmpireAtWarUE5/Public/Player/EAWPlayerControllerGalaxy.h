// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/EAWPlayerControllerBase.h"
#include "EAWPlayerControllerGalaxy.generated.h"

/**
 * 
 */
UCLASS()
class EMPIREATWARUE5_API AEAWPlayerControllerGalaxy : public AEAWPlayerControllerBase
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void EnhancedZoom(const FInputActionValue& Value) override;

	UFUNCTION()
	void OnCameraTravelFinished();

private:
	AEAWPlayerControllerGalaxy();

	UPROPERTY(Transient)
	AActor* CachedSelectedActor;
};
