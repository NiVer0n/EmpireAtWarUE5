// NiVeron Games 2022. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "EAWPlayerPawnBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReachedDestination);

class UCameraComponent;
class ACameraBoundsVolume;
class UCurveFloat;

USTRUCT(BlueprintType)
struct EMPIREATWARUE5_API FTravelSpeedSettings
{
	GENERATED_BODY()

	void SetSpeed(float InSpeed)
	{
		bUseSpeed = true;
		Speed = InSpeed;
	}

	void SetDuration(float InDuration)
	{
		bUseSpeed = false;
		Duration = InDuration;
	}

	bool UseSpeed() const { return bUseSpeed; }
	float GetSpeed() const { return Speed; }
	float GetDuration() const { return Duration; }

private:
	UPROPERTY()
	bool bUseSpeed = true;

	UPROPERTY()
	float Speed = 1000.0f;

	UPROPERTY()
	float Duration = 2.0f;
};

// Unfortunately, TOptional<T> unavailable in BP :(
USTRUCT(BlueprintType)
struct EMPIREATWARUE5_API FOptionalValue
{
	GENERATED_BODY()

	FOptionalValue() {}

	FOptionalValue(const bool InSet, float InValue = 0.0f)
	{
		bIsSet = InSet;
		if (bIsSet)
		{
			Value = InValue;
		}
	}

	FOptionalValue(const float InValue)
	{
		bIsSet = true;
		Value = InValue;
	}

	UPROPERTY()
	bool bIsSet = false;

	UPROPERTY()
	float Value = 0.0f;
};

USTRUCT(BlueprintType)
struct EMPIREATWARUE5_API FTravelSettings
{
	GENERATED_BODY()

	UPROPERTY()
	FVector StartingLocation = FVector::ZeroVector;

	UPROPERTY()
	FOptionalValue StartingYaw;

	UPROPERTY()
	FOptionalValue StartingPitch;

	UPROPERTY()
	FOptionalValue StartingZoom;

	UPROPERTY()
	FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY()
	FTravelSpeedSettings SpeedSettings;

	UPROPERTY()
	FOptionalValue TargetYaw;

	UPROPERTY()
	FOptionalValue TargetPitch;

	UPROPERTY()
	FOptionalValue TargetZoom;

	UPROPERTY()
	FOptionalValue YawDistance;

	UPROPERTY()
	FOptionalValue PitchDistance;

	UPROPERTY()
	FOptionalValue ZoomDistance;
};

USTRUCT(Blueprintable)
struct EMPIREATWARUE5_API FPositionSaveFormat
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FVector DesiredLocation = FVector::ZeroVector;

	UPROPERTY()
	FRotator DesiredRotation = FRotator::ZeroRotator;

	UPROPERTY()
	float DesiredZoom = 0.0f;
};

/**
 * Main player pawn
 */
UCLASS()
class EMPIREATWARUE5_API AEAWPlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Input")
	void MoveForward(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Input")
	void MoveRight(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Input")
	void MoveUp(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Input")
	void RotateYaw(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Input")
	void RotatePitch(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Input")
	void Zoom(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Input")
	void ZoomToCursor(float AxisValue, const ECollisionChannel CollisionChannel, const FVector ImpactPointUnderCursor, float HitResultTraceDistance, bool& DidHit);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Input")
	void SetDesiredPosition(const FVector NewLocation, float NewYaw, float NewPitch, float NewZoom, bool Teleport = false);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Movement")
	void SetDesiredLocation(const FVector NewLocation, bool Teleport = false);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Rotation")
	void SetDesiredYaw(float NewYaw, bool Teleport = false);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Rotation")
	void SetDesiredPitch(float NewPitch, bool Teleport = false);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Zoom")
	void SetDesiredZoom(float NewZoom, bool Teleport = false);

	UFUNCTION(BlueprintPure, Category = "Camera Settings|Zoom")
	FFloatRange GetZoomLimit() const { return ZoomLimit; }

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Travel")
	void TravelToLocation(const FVector TargetLocation, const FTravelSpeedSettings SpeedSettings, FOptionalValue TargetYaw, FOptionalValue TargetPitch, FOptionalValue TargetZoom);

	UFUNCTION(BlueprintPure, Category = "Camera Settings|Movement")
	FORCEINLINE bool GetMovementEnabled() const { return bMovementEnabled; };

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Movement")
	FORCEINLINE void SetMovementEnabled(bool InMovementEnabled) { bMovementEnabled = InMovementEnabled; };

	UFUNCTION(BlueprintPure, Category = "Camera Settings|Zoom")
	FORCEINLINE bool GetZoomEnabled() const { return bZoomEnabled; };

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Zoom")
	FORCEINLINE void SetZoomEnabled(bool InZoomEnabled) { bZoomEnabled = InZoomEnabled; };

	UFUNCTION(BlueprintPure, Category = "Camera Settings|Rotation")
	FORCEINLINE bool GetRotationEnabled() const { return bZoomEnabled; };

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Rotation")
	FORCEINLINE void SetRotationEnabled(bool InRotationEnabled) { bZoomEnabled = InRotationEnabled; };

	UFUNCTION(BlueprintPure, Category = "Camera Settings|Save")
	TArray<uint8> GetSettingsSaveFormat();

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Save")
	void LoadSettingsSaveFormat(const TArray<uint8> ObjectData);

	UFUNCTION(BlueprintPure, Category = "Camera Settings|Save")
	FPositionSaveFormat GetPositionSaveFormat();

	UFUNCTION(BlueprintCallable, Category = "Camera Settings|Save")
	void LoadPositionSaveFormat(const FPositionSaveFormat SaveFormat);

	UFUNCTION(BlueprintPure, Category = "Camera Settings|Save")
	FPositionSaveFormat GetLastSavedPosition() const { return LastSavedPosition; }

	UPROPERTY(BlueprintAssignable)
	FOnReachedDestination OnReachedDestination;

protected:
	AEAWPlayerPawnBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void HandleEdgeScrolling(float DeltaTime);
	void ManageTravelTask(float DeltaTime);

	FORCEINLINE void SetTargetArmLength(float NewLength) { SpringArm->TargetArmLength = NewLength; };

	/* Smooth movement to desired location. */
	FVector GetInterpDesiredLocation(float DeltaTime);

	/* Smooth movement to desired location. */
	FRotator GetInterpDesiredRotation(float DeltaTime);

	/* Smooth movement to desired height. */
	float GetInterpDesiredHeight(float DeltaTime);

	/*	On each Tick, this function will gradually make the Zoom closer to its DesiredZoom. */
	float GetInterpDesiredZoom(float DeltaTime);

	/*	Returns the desired location of the CameraComponent */
	FVector GetDesiredCameraLocation();

	/* Returns true, if there if no ACameraBoundsVolume on level or if DesiredLocation is inside this volume. */
	bool GetIsPermittedLocation(const FVector InLocation) const;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> PawnCamera;

	/* Whether should camera override its starting location. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "Camera Settings|Starting Position")
	bool OverrideStartingLocation;

	/* Overrided starting location value. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "OverrideStartingLocation"), Category = "Camera Settings|Starting Position")
	FVector StartingLocation;

	/* Whether should camera override its starting yaw. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "Camera Settings|Starting Position")
	bool OverrideStartingYaw;

	/* Overrided starting yaw value. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "OverrideStartingYaw"), Category = "Camera Settings|Starting Position")
	float StartingYaw;

	/* Whether should camera override its starting pitch. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "Camera Settings|Starting Position")
	bool OverrideStartingPitch;

	/* Overrided starting pitch value. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "OverrideStartingPitch"), Category = "Camera Settings|Starting Position")
	float StartingPitch;

	/* Whether should camera override its starting zoom. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "Camera Settings|Starting Position")
	bool OverrideStartingZoom;

	/* Overrided starting zoom value. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "OverrideStartingZoom"), Category = "Camera Settings|Starting Position")
	float StartingZoom;

	/* Whether movement enabled. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Movement")
	bool bMovementEnabled;

	/* Whether camera can move on Z-axis. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Movement")
	bool bCanMoveUp;

	/* Default movement speed used in MoveForward/MoveRight. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Camera Settings|Movement")
	float MovementSpeed;

	/* Movement speed multiplier used in MoveForward/MoveRight. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Camera Settings|Movement")
	float MovementSpeedMultiplier;

	/* If true, MoveUp() will always move along the Z axis. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Movement")
	bool UpDirectionIsAbsolute;

	/* The value by which location will change when moving. */
	UPROPERTY(BlueprintReadOnly, Category = "Camera Settings|Movement")
	FVector DesiredLocation;

	/* Whether rotation enabled. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Rotation")
	bool bRotationEnabled;

	/* RotateSpeed is used in RotateYaw(), RotatePitch(), and ScreenSliding when Yaw or Pitch is used. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Camera Settings|Rotation")
	float RotateSpeed;

	/* Rotate speed multiplier used in RotateYaw/RotatePitch. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Camera Settings|Rotation")
	float RotateSpeedMultiplier;

	/* The value by which location will change when rotating. */
	UPROPERTY(BlueprintReadOnly, Category = "Camera Settings|Rotation")
	FRotator DesiredRotation;

	/* Whether zoom enabled */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Zoom")
	bool bZoomEnabled;

	/* Speed of zoom used in Zoom functionality. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Camera Settings|Zoom")
	float ZoomSpeed;

	/* Speed multiplier of zoom used in Zoom functionality. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Camera Settings|Zoom")
	float ZoomSpeedMultiplier;

	/* The value by which spring arm length will change when zooming. */
	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Camera Settings|Zoom")
	float DesiredZoom;

	/* Curve used in TravelToLocation. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Travel")
	TObjectPtr<UCurveFloat> TravelCurve;

	/* Utility variable to store time passed from beginning of the task. */
	UPROPERTY(BlueprintReadOnly, Category = "Camera Settings|Travel")
	float TravelTaskDuration;

	/* Settings for travel task e.g. speed/travel duration, target location, zoom and rotation. */
	UPROPERTY(BlueprintReadOnly, Category = "Camera Settings|Travel")
	FTravelSettings TravelSettings;

	/* Whether camera has active travel task. While its true, all movement/rotation/zoom changes blocked until task finished. */
	UPROPERTY(BlueprintReadOnly, Category = "Camera Settings|Travel")
	bool bTravelTaskActive;

	/* Whether use lag to smoothly move/rotate/zoom. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Lag")
	bool bLagEnabled;

	/* Movement speed when using lag. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Camera Settings|Lag")
	float LagSpeed;

	/* The distance from the edges of the screen at which your cursor must be to edge scroll. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "0.5", UIMax = "0.5"), Category = "Camera Settings|Edge Scrolling")
	float EdgeScrollingSensitivity;

	/* Volume for assigning level boundaries. */
	UPROPERTY(BlueprintReadOnly, Category = "Camera Settings|Restrictions")
	TObjectPtr<ACameraBoundsVolume> CameraBoundsVolume;

	/* Whether should constrain yaw value change. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Restrictions")
	bool ConstrainYaw;

	/* Yaw value limit. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (EditCondition = ConstrainYaw), Category = "Camera Settings|Restrictions")
	FFloatRange YawLimit;

	/* Whether should constrain pitch value change. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Restrictions")
	bool ConstrainPitch;

	/* Pitch value limit. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (EditCondition = ConstrainPitch), Category = "Camera Settings|Restrictions")
	FFloatRange PitchLimit;

	/* Whether should constrain zoom value change. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Restrictions")
	bool ConstrainZoom;

	/* Zoom value limit. */
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Restrictions")
	FFloatRange ZoomLimit;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Camera Settings|Save")
	FPositionSaveFormat LastSavedPosition;

	float m_new;
};
