// NiVeron Games 2022. All right reserved.

#include "Player/EAWPlayerPawnBase.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/CameraBoundsVolume.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

AEAWPlayerPawnBase::AEAWPlayerPawnBase()
	: OverrideStartingLocation(false)
	, StartingLocation(FVector::ZeroVector)
	, OverrideStartingYaw(false)
	, StartingYaw(0.0f)
	, OverrideStartingPitch(false)
	, StartingPitch(-55.0f)
	, OverrideStartingZoom(false)
	, StartingZoom(1000.0f)
	, bMovementEnabled(true)
	, bCanMoveUp(true)
	, MovementSpeed(10.0f)
	, MovementSpeedMultiplier(100.0f)
	, UpDirectionIsAbsolute(true)
	, DesiredLocation(FVector::ZeroVector)
	, bRotationEnabled(true)
	, RotateSpeed(1.4f)
	, RotateSpeedMultiplier(100.0f)
	, DesiredRotation(FRotator::ZeroRotator)
	, bZoomEnabled(true)
	, ZoomSpeed(50.0f)
	, ZoomSpeedMultiplier(1.0f)
	, DesiredZoom(0.0f)
	, TravelCurve(nullptr)
	, TravelTaskDuration(0.0f)
	, TravelSettings()
	, bTravelTaskActive(false)
	, bLagEnabled(true)
	, LagSpeed(5.0f)
	, EdgeScrollingSensitivity(0.1f)
	, CameraBoundsVolume(nullptr)
	, ConstrainYaw(false)
	, YawLimit(0.0f, 0.0f)
	, ConstrainPitch(true)
	, PitchLimit(-89.9f, -10.0f)
	, ConstrainZoom(true)
	, ZoomLimit(250.0f, 2000.0f)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SetTargetArmLength(1000.0f);

	PawnCamera = CreateDefaultSubobject<UCameraComponent>("PawnCamera");
	PawnCamera->SetupAttachment(SpringArm);
}

void AEAWPlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetWorld()))
	{
		CameraBoundsVolume = Cast<ACameraBoundsVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraBoundsVolume::StaticClass()));
	}

	SetDesiredLocation(OverrideStartingLocation ? StartingLocation : GetActorLocation(), true);
	SetDesiredYaw(OverrideStartingYaw ? StartingYaw : GetActorRotation().Yaw, true);
	SetDesiredPitch(OverrideStartingPitch ? StartingPitch : GetActorRotation().Pitch, true);
	SetDesiredZoom(OverrideStartingZoom ? StartingZoom : SpringArm->TargetArmLength, true);
	// @TODO: rewrtite it after implementing save system
	LastSavedPosition = GetPositionSaveFormat();
}

void AEAWPlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ManageTravelTask(DeltaTime);
	HandleEdgeScrolling(DeltaTime);

	if (bLagEnabled)
	{
		SetActorLocation(GetInterpDesiredLocation(DeltaTime));
		const FVector CurrentLocation = GetActorLocation();
		SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, GetInterpDesiredHeight(DeltaTime)));
		SetActorRotation(GetInterpDesiredRotation(DeltaTime));
		SetTargetArmLength(GetInterpDesiredZoom(DeltaTime));
	}
}

void AEAWPlayerPawnBase::HandleEdgeScrolling(float DeltaTime)
{
	if (!bMovementEnabled || bTravelTaskActive)
	{
		return;
	}

	float MouseX, MouseY;
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController->GetMousePosition(MouseX, MouseY))
	{
		return;
	}

	int32 ViewportX, ViewportY;
	PlayerController->GetViewportSize(ViewportX, ViewportY);

	const float XSensitivity = EdgeScrollingSensitivity * ViewportX;
	const float YSensitivity = EdgeScrollingSensitivity * ViewportY;

	if (MouseX < XSensitivity)
	{
		MoveRight(-1.0f);
	}
	else if (MouseX > ViewportX - XSensitivity)
	{
		MoveRight(1.0f);
	}
	if (MouseY < YSensitivity)
	{
		MoveForward(1.0f);
	}
	else if (MouseY > ViewportY - YSensitivity)
	{
		MoveForward(-1.0f);
	}
}

void AEAWPlayerPawnBase::MoveForward(float AxisValue)
{
	if (!bMovementEnabled || bTravelTaskActive)
	{
		return;
	}

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(DesiredRotation);
	ForwardVector.Z = 0.0f;
	ForwardVector.Normalize();
	if (ForwardVector.Size() <= KINDA_SMALL_NUMBER)
	{
		ForwardVector = UKismetMathLibrary::GetRightVector(DesiredRotation).RotateAngleAxis(90.0f, UKismetMathLibrary::GetForwardVector(DesiredRotation));
	}

	if (IsValid(GetWorld()))
	{
		SetDesiredLocation(DesiredLocation + ForwardVector * GetWorld()->GetDeltaSeconds() * AxisValue * MovementSpeed * MovementSpeedMultiplier);
	}
}

void AEAWPlayerPawnBase::MoveRight(float AxisValue)
{
	if (!bMovementEnabled || bTravelTaskActive)
	{
		return;
	}

	const FVector RightVector = UKismetMathLibrary::GetRightVector(DesiredRotation);
	if (IsValid(GetWorld()))
	{
		SetDesiredLocation(DesiredLocation + RightVector * GetWorld()->GetDeltaSeconds() * AxisValue * MovementSpeed * MovementSpeedMultiplier);
	}
}

void AEAWPlayerPawnBase::MoveUp(float AxisValue)
{
	if (!bMovementEnabled || bTravelTaskActive || !bCanMoveUp)
	{
		return;
	}

	const FVector UpVector = UpDirectionIsAbsolute ? FVector::UpVector : UKismetMathLibrary::GetUpVector(DesiredRotation);
	if (IsValid(GetWorld()))
	{
		SetDesiredLocation(DesiredLocation + UpVector * GetWorld()->GetDeltaSeconds() * AxisValue * MovementSpeed * MovementSpeedMultiplier);
	}
}

void AEAWPlayerPawnBase::RotateYaw(float AxisValue)
{
	if (bRotationEnabled && !bTravelTaskActive && IsValid(GetWorld()))
	{
		SetDesiredYaw(DesiredRotation.Yaw - GetWorld()->GetDeltaSeconds() * AxisValue * RotateSpeed * RotateSpeedMultiplier);
	}
}

void AEAWPlayerPawnBase::RotatePitch(float AxisValue)
{
	if (bRotationEnabled && !bTravelTaskActive && IsValid(GetWorld()))
	{
		SetDesiredPitch(DesiredRotation.Pitch - GetWorld()->GetDeltaSeconds() * AxisValue * RotateSpeed * RotateSpeedMultiplier);
	}
}

void AEAWPlayerPawnBase::Zoom(float AxisValue)
{
	if (bZoomEnabled && !bTravelTaskActive)
	{
		SetDesiredZoom(DesiredZoom - AxisValue * ZoomSpeedMultiplier * ZoomSpeed);
	}
}

void AEAWPlayerPawnBase::ZoomToCursor(float AxisValue, const ECollisionChannel CollisionChannel, const FVector ImpactPointUnderCursor, float HitResultTraceDistance, bool& DidHit)
{
	if (!bZoomEnabled || bTravelTaskActive)
	{
		return;
	}

	FVector Direction = ImpactPointUnderCursor - GetDesiredCameraLocation();
	Direction.Normalize();
	Direction *= HitResultTraceDistance;

	Zoom(AxisValue);

	if (!DidHit || !IsValid(GetWorld()))
	{
		return;
	}

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, GetDesiredCameraLocation(), GetDesiredCameraLocation() + Direction, CollisionChannel);
	if (HitResult.IsValidBlockingHit())
	{
		FVector Impact = HitResult.ImpactPoint;
		FVector Correction = ImpactPointUnderCursor - Impact;
		SetDesiredLocation(FVector(DesiredLocation.X + Correction.X, DesiredLocation.Y + Correction.Y, DesiredLocation.Z));
	}
}

void AEAWPlayerPawnBase::SetDesiredPosition(const FVector NewLocation, float NewYaw, float NewPitch, float NewZoom, bool Teleport)
{
	SetDesiredLocation(NewLocation, Teleport);
	SetDesiredYaw(NewYaw, Teleport);
	SetDesiredPitch(NewPitch, Teleport);
	SetDesiredZoom(NewZoom, Teleport);
}

void AEAWPlayerPawnBase::SetDesiredLocation(const FVector NewLocation, bool Teleport)
{
	if (!GetIsPermittedLocation(NewLocation))
	{
		return;
	}

	DesiredLocation = NewLocation;
	if (!bLagEnabled || Teleport)
	{
		SetActorLocation(DesiredLocation);
	}
}

void AEAWPlayerPawnBase::SetDesiredYaw(float NewYaw, bool Teleport)
{
	if (ConstrainYaw)
	{
		NewYaw = FMath::Clamp(NewYaw, YawLimit.GetLowerBoundValue(), YawLimit.GetUpperBoundValue());
	}

	if (NewYaw > 180)
	{
		NewYaw -= 360;
	}
	else if (NewYaw < -180)
	{
		NewYaw += 360;
	}

	DesiredRotation.Yaw = NewYaw;
	if (!bLagEnabled || Teleport)
	{
		SetActorRotation(DesiredRotation);
	}
}

void AEAWPlayerPawnBase::SetDesiredPitch(float NewPitch, bool Teleport)
{
	if (ConstrainPitch)
	{
		NewPitch = FMath::Clamp(NewPitch, PitchLimit.GetLowerBoundValue(), PitchLimit.GetUpperBoundValue());
	}

	DesiredRotation.Pitch = NewPitch;
	if (!bLagEnabled || Teleport)
	{
		SetActorRotation(DesiredRotation);
	}
}

void AEAWPlayerPawnBase::SetDesiredZoom(float NewZoom, bool Teleport)
{
	DesiredZoom = FMath::Clamp(NewZoom, ZoomLimit.GetLowerBoundValue(), ZoomLimit.GetUpperBoundValue());

	if (!bLagEnabled || Teleport)
	{
		SetTargetArmLength(DesiredZoom);
	}
}

void AEAWPlayerPawnBase::TravelToLocation(const FVector TargetLocation, const FTravelSpeedSettings SpeedSettings, FOptionalValue TargetYaw, FOptionalValue TargetPitch, FOptionalValue TargetZoom)
{
	TravelSettings.TargetLocation = TargetLocation;
	TravelSettings.SpeedSettings = SpeedSettings;

	TravelSettings.StartingLocation = DesiredLocation;
	TravelSettings.StartingYaw.Value = DesiredRotation.Yaw;
	TravelSettings.StartingPitch.Value = DesiredRotation.Pitch;
	TravelSettings.StartingZoom.Value = DesiredZoom;

	if (TargetYaw.bIsSet)
	{
		if (TravelSettings.StartingYaw.Value - TargetYaw.Value > 180.0f)
		{
			TargetYaw.Value += 360.0f;
		}
		else if (TravelSettings.StartingYaw.Value - TargetYaw.Value < -180.0f)
		{
			TargetYaw.Value -= 360.0f;
		}
		TravelSettings.YawDistance.Value = TargetYaw.Value - TravelSettings.StartingYaw.Value;
		TravelSettings.YawDistance.bIsSet = true;
		TravelSettings.TargetYaw.Value = TargetYaw.Value;
		TravelSettings.TargetYaw.bIsSet = true;
	}

	if (TargetPitch.bIsSet)
	{
		TravelSettings.PitchDistance.Value = TargetPitch.Value - TravelSettings.StartingPitch.Value;
		TravelSettings.PitchDistance.bIsSet = true;
		TravelSettings.TargetPitch.Value = TargetPitch.Value;
		TravelSettings.TargetPitch.bIsSet = true;
	}

	if (TargetZoom.bIsSet)
	{
		TravelSettings.ZoomDistance.Value = TargetZoom.Value - TravelSettings.StartingZoom.Value;
		TravelSettings.ZoomDistance.bIsSet = true;
		TravelSettings.TargetZoom.Value = TargetZoom.Value;
		TravelSettings.TargetZoom.bIsSet = true;
	}

	bTravelTaskActive = true;
}

void AEAWPlayerPawnBase::ManageTravelTask(float DeltaTime)
{
	if (!bTravelTaskActive)
	{
		return;
	}

	if (!ensureMsgf(IsValid(TravelCurve), TEXT("%s: TravelCurve isn't set!"), ANSI_TO_TCHAR("__FUNCTION__")))
	{
		return;
	}

	TravelTaskDuration += DeltaTime;
	const FVector Direction = TravelSettings.TargetLocation - TravelSettings.StartingLocation;
	const float Multiplier = TravelSettings.SpeedSettings.UseSpeed() ? 
		Direction.Length() / TravelSettings.SpeedSettings.GetSpeed() : 
		TravelSettings.SpeedSettings.GetDuration();

	if (Multiplier == 0.0f)
	{
		return;
	}

	const float CurrentCurvePosition = TravelTaskDuration / Multiplier;
	
	if (CurrentCurvePosition >= 1.0f)
	{
		SetDesiredLocation(TravelSettings.TargetLocation);
		
		if (TravelSettings.TargetYaw.bIsSet)
		{
			SetDesiredYaw(TravelSettings.TargetYaw.Value);
		}

		if (TravelSettings.TargetPitch.bIsSet)
		{
			SetDesiredPitch(TravelSettings.TargetPitch.Value);
		}

		if (TravelSettings.TargetZoom.bIsSet)
		{
			SetDesiredZoom(TravelSettings.TargetZoom.Value);
		}

		OnReachedDestination.Broadcast();
		bTravelTaskActive = false;
		TravelTaskDuration = 0.0f;
	}
	else
	{
		const float Position = TravelCurve->GetFloatValue(CurrentCurvePosition);
		SetDesiredLocation(TravelSettings.StartingLocation + Direction * Position);

		if (TravelSettings.TargetYaw.bIsSet)
		{
			SetDesiredYaw(TravelSettings.StartingYaw.Value + TravelSettings.YawDistance.Value * Position);
		}

		if (TravelSettings.TargetPitch.bIsSet)
		{
			SetDesiredPitch(TravelSettings.StartingPitch.Value + TravelSettings.PitchDistance.Value * Position);
		}

		if (TravelSettings.TargetZoom.bIsSet)
		{
			SetDesiredZoom(TravelSettings.StartingZoom.Value + TravelSettings.ZoomDistance.Value * Position);
		}
	}
}

FVector AEAWPlayerPawnBase::GetInterpDesiredLocation(float DeltaTime)
{
	const FVector CurrentLocation = GetActorLocation();
	const FVector2D InterpolatedLocation = FMath::Vector2DInterpTo(FVector2D(CurrentLocation.X, CurrentLocation.Y), FVector2D(DesiredLocation.X, DesiredLocation.Y), DeltaTime, LagSpeed);
	const FVector FinalLocation = FVector(InterpolatedLocation.X, InterpolatedLocation.Y, CurrentLocation.Z);
	return GetIsPermittedLocation(FinalLocation) ? FinalLocation : CurrentLocation;
}

FRotator AEAWPlayerPawnBase::GetInterpDesiredRotation(float DeltaTime)
{
	return FRotator(FMath::QInterpTo(FQuat(GetActorRotation()), FQuat(DesiredRotation), DeltaTime, LagSpeed));
}

float AEAWPlayerPawnBase::GetInterpDesiredHeight(float DeltaTime)
{
	return FMath::FInterpTo(GetActorLocation().Z, DesiredLocation.Z, DeltaTime, LagSpeed);
}

float AEAWPlayerPawnBase::GetInterpDesiredZoom(float DeltaTime)
{
	return FMath::FInterpTo(SpringArm->TargetArmLength, DesiredZoom, DeltaTime, LagSpeed);
}

FVector AEAWPlayerPawnBase::GetDesiredCameraLocation()
{
	return DesiredLocation + UKismetMathLibrary::GetForwardVector(DesiredRotation) * -1.0f * DesiredZoom;
}

bool AEAWPlayerPawnBase::GetIsPermittedLocation(const FVector InLocation) const
{
	return !IsValid(CameraBoundsVolume) || CameraBoundsVolume->EncompassesPoint(InLocation);
}

TArray<uint8> AEAWPlayerPawnBase::GetSettingsSaveFormat()
{
	TArray<uint8> ObjectData;
	FMemoryWriter MemoryWriter(ObjectData, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, false);
	Ar.ArNoDelta = true;
	this->Serialize(Ar);
	return ObjectData;
}

void AEAWPlayerPawnBase::LoadSettingsSaveFormat(const TArray<uint8> ObjectData)
{
	FMemoryReader MemoryReader(ObjectData, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryReader, false);
	Ar.ArIsSaveGame = true;
	Ar.ArNoDelta = true;
	this->Serialize(Ar);
}

FPositionSaveFormat AEAWPlayerPawnBase::GetPositionSaveFormat()
{
	FPositionSaveFormat SaveFormat;
	SaveFormat.DesiredLocation = DesiredLocation;
	SaveFormat.DesiredRotation = DesiredRotation;
	SaveFormat.DesiredZoom = DesiredZoom;

	return SaveFormat;
}

void AEAWPlayerPawnBase::LoadPositionSaveFormat(const FPositionSaveFormat SaveFormat)
{
	SetDesiredPosition(
		SaveFormat.DesiredLocation, 
		SaveFormat.DesiredRotation.Yaw, 
		SaveFormat.DesiredRotation.Pitch, 
		SaveFormat.DesiredZoom, true);
}
