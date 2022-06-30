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

public:
	FORCEINLINE AActor* GetSelectedActor() const { return SelectedActor; };

protected:
	AEAWPlayerControllerGalaxy(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void EnhancedStartPrimaryAction(const FInputActionValue& Value) override;
	virtual void EnhancedZoomCamera(const FInputActionValue& Value) override;
	void TimelineProgress(float Value);
	void TimelineFinished();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
	FFloatRange ZoomLimit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
	FVector ZoomedCameraOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Zoom")
	UCurveFloat* CurveFloat;

private:
	AActor* GetActorUnderCursor();
	void SelectActor();
	void SetSelectionVisibility(bool Visible);

	FVector GetZoomedCameraLocation() const;

	UPROPERTY(Transient)
	AActor* SelectedActor;

	UPROPERTY()
	bool bZoomInProgress;

	UPROPERTY()
	bool bIsZoomed;

	UPROPERTY()
	FTimeline CurveTimeline;

	FOnTimelineFloatStatic OnTimelineProgress;
	FOnTimelineEventStatic OnTimelineFinished;
};
