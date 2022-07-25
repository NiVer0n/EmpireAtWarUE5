// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/EAWPlayerControllerBase.h"
#include "Components/TimelineComponent.h"
#include "EAWPlayerControllerGalaxy.generated.h"

class UCurveFloat;

/**
 * 
 */
UCLASS()
class EMPIREATWARUE5_API AEAWPlayerControllerGalaxy : public AEAWPlayerControllerBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void EnhancedStartPrimaryAction(const FInputActionValue& Value) override;
	virtual void EnhancedZoomCamera(const FInputActionValue& Value) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
	UCurveFloat* CurveFloat;

private:
	AEAWPlayerControllerGalaxy();

	void TimelineProgress(float Value);
	void TimelineFinished();

	FVector GetZoomedCameraLocation() const;

	UPROPERTY(Transient)
	AActor* CachedSelectedActor;

	UPROPERTY()
	bool bZoomInProgress;

	UPROPERTY()
	float ZoomValue;

	UPROPERTY(Transient)
	FTimeline CurveTimeline;

	FOnTimelineFloatStatic OnTimelineProgress;
	FOnTimelineEventStatic OnTimelineFinished;
};
