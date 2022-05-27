// NiVeron Games 2022. All right reserved.

#include "Player/EAWPlayerPawnBase.h"
#include "Camera/CameraComponent.h"

AEAWPlayerPawnBase::AEAWPlayerPawnBase()
{
	CameraSettings.Angle = FRotator(-55.0f, 0.0f, 0.0f);
	CameraSettings.Speed = 1000.0f;
	CameraSettings.SpeedMultiplier = 1.0f;
	CameraSettings.LagSpeed = 3.0f;
	CameraSettings.ZoomSpeed = 5.0f;
	CameraSettings.ZoomModifier = 50.0f;
	CameraSettings.MinDistance = 300.0f;
	CameraSettings.MaxDistance = 2000.0f;
	CameraSettings.CurrentZoom = 1000.0f;
	CameraSettings.DesiredZoom = 1000.0f;
	CameraSettings.ScrollThreshold = 20;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SetTargetArmLength(CameraSettings.CurrentZoom);
	SpringArm->SetRelativeRotation(CameraSettings.Angle);
	SetCameraLagEnabled(true);
	SpringArm->CameraLagSpeed = CameraSettings.LagSpeed;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	PawnCamera->SetupAttachment(SpringArm);
	/* Camera movement is configured in the controller */
	bAddDefaultMovementBindings = false;
}