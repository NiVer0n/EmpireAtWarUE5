// NiVeron Games 2022. All rights reserved.

#include "Player/EAWPlayerControllerGalaxy.h"
#include "Components/SelectionComponent.h"
#include "Components/NameComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameplay/StarSystem.h"

AEAWPlayerControllerGalaxy::AEAWPlayerControllerGalaxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ZoomLimit(FFloatRange(125.0f, 1000.0f))
	, ZoomedCameraOffset(FVector(0.0f, 50.0f, 0.0f))
	, CachedSelectedStarSystem(nullptr)
	, bZoomInProgress(false)
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
		TrySelectActor(GetActorUnderCursor());
	}
}

void AEAWPlayerControllerGalaxy::EnhancedZoomCamera(const FInputActionValue& Value)
{
	if (bZoomInProgress)
	{
		return;
	}

	const bool bIsZoomedIn = Value[0] > 0.0f;
	if (bIsZoomedIn)
	{
		TrySelectActor(GetActorUnderCursor());
	}
	PlayerPawn->SetCameraLagEnabled(false);

	CameraSettings.DesiredZoom = bIsZoomedIn ? ZoomLimit.GetLowerBoundValue() : ZoomLimit.GetUpperBoundValue();
	bZoomInProgress = true;
	SetMovementEnabled(!bIsZoomedIn);
	CachedSelectedStarSystem->GetSelectionComponent()->SetCanBeSelected(!bIsZoomedIn);
	CachedSelectedStarSystem->GetSelectionComponent()->OnSetSelected.Broadcast(!bIsZoomedIn);
	CachedSelectedStarSystem->SetNameVisibility(!bIsZoomedIn);
	CurveTimeline.PlayFromStart();
}

AActor* AEAWPlayerControllerGalaxy::GetActorUnderCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	return HitResult.GetActor();
}

void AEAWPlayerControllerGalaxy::TrySelectActor(AActor* InSelectedActor)
{
	if (IsValid(CachedSelectedStarSystem))
	{
		CachedSelectedStarSystem->GetSelectionComponent()->OnSetSelected.Broadcast(false);
		CachedSelectedStarSystem = nullptr;
	}

	AStarSystem* SelectedStarSystem = Cast<AStarSystem>(InSelectedActor);
	if (!IsValid(SelectedStarSystem) || !SelectedStarSystem->GetSelectionComponent()->GetCanBeSelected())
	{
		return;
	}

	CachedSelectedStarSystem = SelectedStarSystem;
	CachedSelectedStarSystem->GetSelectionComponent()->OnSetSelected.Broadcast(true);
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
	const FVector DesiredLocation = CachedSelectedStarSystem->GetActorLocation() - ZoomedCameraOffset;
	return FMath::VInterpTo(CurrentLocation, DesiredLocation, GetWorld()->GetDeltaSeconds(), CameraSettings.ZoomSpeed);
}
