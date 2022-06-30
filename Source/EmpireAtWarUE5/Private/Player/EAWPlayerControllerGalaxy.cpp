// NiVeron Games 2022. All rights reserved.

#include "Player/EAWPlayerControllerGalaxy.h"
#include "Components/SelectionComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"

AEAWPlayerControllerGalaxy::AEAWPlayerControllerGalaxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SelectedActor = nullptr;
	bZoomInProgress = false;
	bIsZoomed = false;
	ZoomLimit = FFloatRange(125.0f, 1000.0f);
	ZoomedCameraOffset = FVector(0.0f, 50.0f, 0.0f);
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
	if (bZoomInProgress)
	{
		return;
	}
	SelectActor();
}

void AEAWPlayerControllerGalaxy::EnhancedZoomCamera(const FInputActionValue& Value)
{
	if (bZoomInProgress)
	{
		return;
	}
	if (IsValid(GetActorUnderCursor()))
	{
		SelectActor();
	}
	else if (!IsValid(SelectedActor))
	{
		return;
	}
	PlayerPawn->SetCameraLagEnabled(false);

	bIsZoomed = Value[0] > 0;
	CameraSettings.DesiredZoom = bIsZoomed ? ZoomLimit.GetLowerBoundValue() : ZoomLimit.GetUpperBoundValue();
	bZoomInProgress = true;
	SetMovementEnabled(!bIsZoomed);
	SetSelectionVisibility(!bIsZoomed);
	CurveTimeline.PlayFromStart();
}

AActor* AEAWPlayerControllerGalaxy::GetActorUnderCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	return HitResult.GetActor();
}

void AEAWPlayerControllerGalaxy::SelectActor()
{
	SetSelectionVisibility(false);
	SelectedActor = GetActorUnderCursor();
	SetSelectionVisibility(true);
}

void AEAWPlayerControllerGalaxy::SetSelectionVisibility(bool Visible)
{
	if (!IsValid(SelectedActor))
	{
		return;
	}
	if (USelectionComponent* SelectionComponent = SelectedActor->FindComponentByClass<USelectionComponent>())
	{
		Visible ? SelectionComponent->OnSelected.Broadcast() : SelectionComponent->OnDeselected.Broadcast();
	}
}

void AEAWPlayerControllerGalaxy::TimelineProgress(float Value)
{
	CameraSettings.CurrentZoom = UKismetMathLibrary::Ease(CameraSettings.CurrentZoom, CameraSettings.DesiredZoom, Value, EEasingFunc::ExpoIn);
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
	const FVector DesiredLocation = SelectedActor->GetActorLocation() - ZoomedCameraOffset;
	return FMath::VInterpTo(CurrentLocation, DesiredLocation, GetWorld()->GetDeltaSeconds(), CameraSettings.ZoomSpeed);
}