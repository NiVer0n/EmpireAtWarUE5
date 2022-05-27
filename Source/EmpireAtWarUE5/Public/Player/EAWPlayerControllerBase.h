// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player/EAWPlayerPawnBase.h"
#include "EAWPlayerControllerBase.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class ACameraBoundsVolume;

/**
 * 
 */
UCLASS()
class EMPIREATWARUE5_API AEAWPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AEAWPlayerControllerBase(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE void SetMovementEnabled(bool MovementEnabled) { bIsMovementEnabled = MovementEnabled; };
	/** Return mouse 2D position vector converted to 3d vector */
	FORCEINLINE FVector GetMousePositionInWorldSpace();
	FORCEINLINE ACameraBoundsVolume* GetCameraBoundsVolume() const { return CameraBoundsVolume; };
	FORCEINLINE FVector2D GetSelectionStartPoint() const { return SelectionStartPoint; };

	FVector2D GetCurrentMousePosition();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void EnhancedStartPrimaryAction(const FInputActionValue& Value) {};
	virtual void EnhancedZoomCamera(const FInputActionValue& Value);
	virtual void UpdateCameraZoom(float DeltaTime);

	UPROPERTY(Transient)
	AEAWPlayerPawnBase* PlayerPawn;

	UPROPERTY(Transient)
	FCameraSettings CameraSettings;

private:
	void EnhancedMove(const FInputActionValue& Value);
	void UpdateCameraMovement(float DeltaTime);

	UPROPERTY(Transient)
	ACameraBoundsVolume* CameraBoundsVolume;

	UPROPERTY()
	bool bIsMovementEnabled;

	UPROPERTY()
	FVector2D CameraMovementAxisValue;

	UPROPERTY()
	float CameraZoomAxisValue;

	UPROPERTY()
	FVector2D SelectionStartPoint;
};
