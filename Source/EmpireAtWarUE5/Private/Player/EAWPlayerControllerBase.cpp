// NiVeron Games 2022. All rights reserved.

#include "Player/EAWPlayerControllerBase.h"
#include "Components/EAWInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/CameraBoundsVolume.h"
#include "InputTriggers.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"

AEAWPlayerControllerBase::AEAWPlayerControllerBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerPawn = nullptr;
	CameraSettings = FCameraSettings();
	CameraBoundsVolume = nullptr;
	bIsMovementEnabled = true;
	CameraMovementAxisValue = FVector2D::ZeroVector;
	CameraZoomAxisValue = 0.0f;
	SelectionStartPoint = FVector2D::ZeroVector;
}

void AEAWPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	FInputModeGameAndUI InputMode = FInputModeGameAndUI();
	SetInputMode(InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways));

	UEAWInputComponent* EAWInputComponent = Cast<UEAWInputComponent>(InputComponent);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem && EAWInputComponent);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(EAWInputComponent->GetMappingContext(), 0);
	
	EAWInputComponent->BindAction(EAWInputComponent->GetMovementAction(), ETriggerEvent::Triggered, this, &AEAWPlayerControllerBase::EnhancedMove);
	EAWInputComponent->BindAction(EAWInputComponent->GetMouseAction(), ETriggerEvent::Started, this, &AEAWPlayerControllerBase::EnhancedStartPrimaryAction);
	EAWInputComponent->BindAction(EAWInputComponent->GetZoomAction(), ETriggerEvent::Triggered, this, &AEAWPlayerControllerBase::EnhancedZoomCamera);
}

void AEAWPlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerPawn = Cast<AEAWPlayerPawnBase>(InPawn);
	checkf(IsValid(PlayerPawn), TEXT("AEAWPlayerControllerBase::OnPossess(APawn* InPawn): PlayerPawn returns null."));

	CameraSettings = PlayerPawn->GetCameraSettings();
	checkf(IsValid(GetWorld()), TEXT("AEAWPlayerControllerBase::SetupInputComponent(): GetWorld() returns null."));
	CameraBoundsVolume = Cast<ACameraBoundsVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraBoundsVolume::StaticClass()));
}

void AEAWPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateCameraMovement(DeltaTime);
	UpdateCameraZoom(DeltaTime);
}

void AEAWPlayerControllerBase::EnhancedMove(const FInputActionValue& Value)
{
	CameraMovementAxisValue.X = Value[0];
	CameraMovementAxisValue.Y = Value[1];
}

void AEAWPlayerControllerBase::EnhancedZoomCamera(const FInputActionValue& Value)
{
	CameraSettings.DesiredZoom = FMath::Clamp(CameraSettings.DesiredZoom + Value[0] * CameraSettings.ZoomModifier * -1.0f, CameraSettings.MinDistance, CameraSettings.MaxDistance);
}

void AEAWPlayerControllerBase::UpdateCameraMovement(float DeltaTime)
{
	if (!bIsMovementEnabled) return;

	FVector2D ViewportSize, ScrollBorder;
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ScrollBorder.X = ViewportSize.X - CameraSettings.ScrollThreshold;
	ScrollBorder.Y = ViewportSize.Y - CameraSettings.ScrollThreshold;
	// Detect if cursor approach to the edge
	const FVector2D MousePosition = GetCurrentMousePosition();
	if (MousePosition.X <= CameraSettings.ScrollThreshold)
	{
		CameraMovementAxisValue.X -= 1.0f - (MousePosition.X / CameraSettings.ScrollThreshold);
	}
	else if (MousePosition.X >= ScrollBorder.X)
	{
		CameraMovementAxisValue.X += (MousePosition.X - ScrollBorder.X) / CameraSettings.ScrollThreshold;
	}

	if (MousePosition.Y <= CameraSettings.ScrollThreshold)
	{
		CameraMovementAxisValue.Y += 1.0f - (MousePosition.Y / CameraSettings.ScrollThreshold);
	}
	else if (MousePosition.Y >= ScrollBorder.Y)
	{
		CameraMovementAxisValue.Y -= (MousePosition.Y - ScrollBorder.Y) / CameraSettings.ScrollThreshold;
	}

	CameraMovementAxisValue.X = FMath::Clamp(CameraMovementAxisValue.X, -1.0f, 1.0f);
	CameraMovementAxisValue.Y = FMath::Clamp(CameraMovementAxisValue.Y, -1.0f, 1.0f);

	if (CameraMovementAxisValue.X != 0.0f || CameraMovementAxisValue.Y != 0.0f)
	{
		FVector Location = PlayerPawn->GetActorLocation();
		Location += FVector::ForwardVector * CameraSettings.Speed * CameraSettings.SpeedMultiplier * CameraMovementAxisValue.Y * DeltaTime;
		Location += FVector::RightVector * CameraSettings.Speed * CameraSettings.SpeedMultiplier * CameraMovementAxisValue.X * DeltaTime;

		if (!CameraBoundsVolume || CameraBoundsVolume->EncompassesPoint(Location))
		{
			PlayerPawn->SetActorLocation(Location);
		}
	}
	CameraMovementAxisValue = FVector2D::ZeroVector;
}

void AEAWPlayerControllerBase::UpdateCameraZoom(float DeltaTime)
{
	if (CameraSettings.CurrentZoom == CameraSettings.DesiredZoom) return;
	CameraSettings.CurrentZoom = FMath::FInterpTo(CameraSettings.CurrentZoom, CameraSettings.DesiredZoom, DeltaTime, CameraSettings.ZoomSpeed);
	PlayerPawn->SetTargetArmLength(CameraSettings.CurrentZoom);
}

FVector AEAWPlayerControllerBase::GetMousePositionInWorldSpace()
{
	FVector WorldLocation, WorldDirection;
	if (!DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) return FVector();
	return WorldLocation - WorldDirection * (WorldLocation.Z / WorldDirection.Z);
}

FVector2D AEAWPlayerControllerBase::GetCurrentMousePosition()
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);
	return FVector2D(MouseX, MouseY);
}