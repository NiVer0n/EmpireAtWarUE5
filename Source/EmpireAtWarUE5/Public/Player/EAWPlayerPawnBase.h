// NiVeron Games 2022. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "EAWPlayerPawnBase.generated.h"

USTRUCT(BlueprintType)
struct FCameraSettings
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	FRotator Angle;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float Speed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float SpeedMultiplier;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float LagSpeed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float ZoomSpeed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float ZoomModifier;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float MinDistance;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float MaxDistance;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	float CurrentZoom;

	UPROPERTY()
	float DesiredZoom;
	/* Distance from the screen border at which the mouse cursor causes the camera to move, in pixels. */
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0))
	int32 ScrollThreshold;
};
/**
 * Main player pawn (player camera)
 */
UCLASS()
class EMPIREATWARUE5_API AEAWPlayerPawnBase : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	FORCEINLINE FCameraSettings GetCameraSettings() const { return CameraSettings; };
	FORCEINLINE void SetTargetArmLength(float NewLength) { SpringArm->TargetArmLength = NewLength; };
	FORCEINLINE void SetCameraLagEnabled(bool Enabled) { SpringArm->bEnableCameraLag = Enabled; };

protected:
	AEAWPlayerPawnBase();

	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	FCameraSettings CameraSettings;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* PawnCamera;
};
