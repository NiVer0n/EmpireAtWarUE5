// NiVeron Games 2022. All rights reserved.

#include "Player/EAWPlayerControllerGalaxy.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/Zoomable.h"

AEAWPlayerControllerGalaxy::AEAWPlayerControllerGalaxy()
	: CachedSelectedActor(nullptr)
	, bZoomInProgress(false)
	, ZoomValue(0.0f)
{
}

void AEAWPlayerControllerGalaxy::BeginPlay()
{
	Super::BeginPlay();

	ensure(CurveFloat);

	OnTimelineProgress.BindUObject(this, &AEAWPlayerControllerGalaxy::TimelineProgress);
	OnTimelineFinished.BindUObject(this, &AEAWPlayerControllerGalaxy::TimelineFinished);
	CurveTimeline.AddInterpFloat(CurveFloat, OnTimelineProgress);
	CurveTimeline.SetTimelineFinishedFunc(OnTimelineFinished);
}

void AEAWPlayerControllerGalaxy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnTimelineProgress.Unbind();
	OnTimelineFinished.Unbind();
}

void AEAWPlayerControllerGalaxy::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);
}

void AEAWPlayerControllerGalaxy::EnhancedStartPrimaryAction(const FInputActionValue& Value)
{
	if (!bZoomInProgress)
	{
		Super::EnhancedStartPrimaryAction(Value);
	}
}

void AEAWPlayerControllerGalaxy::EnhancedZoomCamera(const FInputActionValue& Value)
{
	const bool bIsZoomedIn = Value[0] > 0.0f;
	ZoomValue = bIsZoomedIn ? CameraSettings.ZoomLimit.GetLowerBoundValue() : CameraSettings.ZoomLimit.GetUpperBoundValue();
	if (bZoomInProgress || CameraSettings.CurrentZoom == ZoomValue)
	{
		return;
	}
	if (bIsZoomedIn)
	{
		TrySelectActor();
	}
	CachedSelectedActor = SelectedActors.Last();
	if (!IsValid(CachedSelectedActor) || !CachedSelectedActor->Implements<UZoomable>())
	{
		return;
	}
	IZoomable::Execute_ZoomToObject(CachedSelectedActor, bIsZoomedIn);
	
	PlayerPawn->SetCameraLagEnabled(false);
	CameraSettings.DesiredZoom = ZoomValue;
	bZoomInProgress = true;
	SetMovementEnabled(!bIsZoomedIn);
	CurveTimeline.PlayFromStart();
}

void AEAWPlayerControllerGalaxy::TimelineProgress(float Value)
{
	CameraSettings.CurrentZoom = UKismetMathLibrary::Ease(CameraSettings.CurrentZoom, CameraSettings.DesiredZoom, Value, EEasingFunc::ExpoIn);
	//CameraSettings.DesiredZoom = UKismetMathLibrary::Ease(CameraSettings.CurrentZoom, ZoomValue, Value, EEasingFunc::ExpoIn);
	PlayerPawn->SetActorLocation(GetZoomedCameraLocation());
}

void AEAWPlayerControllerGalaxy::TimelineFinished()
{
	bZoomInProgress = false;
	PlayerPawn->SetCameraLagEnabled(true);
}

FVector AEAWPlayerControllerGalaxy::GetZoomedCameraLocation() const
{
	const FVector CurrentLocation = PlayerPawn->GetActorLocation();
	const FVector DesiredLocation = CachedSelectedActor->GetActorLocation() - CameraSettings.ZoomedCameraOffset;
	return FMath::VInterpTo(CurrentLocation, DesiredLocation, GetWorld()->GetDeltaSeconds(), CameraSettings.ZoomSpeed);
}
