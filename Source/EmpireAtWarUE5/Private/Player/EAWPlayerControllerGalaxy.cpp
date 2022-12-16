// NiVeron Games 2022. All rights reserved.

#include "Player/EAWPlayerControllerGalaxy.h"
#include "InputActionValue.h"
#include "Interfaces/Zoomable.h"
#include "Interfaces/Selectable.h"
#include "Player/EAWPlayerPawnBase.h"

AEAWPlayerControllerGalaxy::AEAWPlayerControllerGalaxy()
	: CachedSelectedActor(nullptr)
{
}

void AEAWPlayerControllerGalaxy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerPawn->OnReachedDestination.AddUniqueDynamic(this, &ThisClass::OnCameraTravelFinished);
}

void AEAWPlayerControllerGalaxy::EnhancedZoom(const FInputActionValue& Value)
{
	if (!IsValid(PlayerPawn))
	{
		return;
	}

	const bool bIsZoomedIn = Value[0] > 0.0f;
	if (bIsZoomedIn)
	{
		TrySelectActor();
	}

	if (SelectedActors.IsEmpty())
	{
		return;
	}

	CachedSelectedActor = SelectedActors.Last();
	if (!IsValid(CachedSelectedActor) || !CachedSelectedActor->Implements<UZoomable>())
	{
		return;
	}
	IZoomable::Execute_ZoomToObject(CachedSelectedActor, bIsZoomedIn);
	const float ZoomValue = bIsZoomedIn ? PlayerPawn->GetZoomLimit().GetLowerBoundValue() : PlayerPawn->GetZoomLimit().GetUpperBoundValue();
	FTravelSpeedSettings SpeedSettings;
	SpeedSettings.SetDuration(0.5f);
	PlayerPawn->TravelToLocation(CachedSelectedActor->GetActorLocation(), SpeedSettings, FOptionalValue(false), FOptionalValue(false), FOptionalValue(ZoomValue));
}

void AEAWPlayerControllerGalaxy::OnCameraTravelFinished()
{
	if (IsValid(PlayerPawn))
	{
		PlayerPawn->SetMovementEnabled(!PlayerPawn->GetMovementEnabled());
		PlayerPawn->SetRotationEnabled(!PlayerPawn->GetRotationEnabled());
	}
}
