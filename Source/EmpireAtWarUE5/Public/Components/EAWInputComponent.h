// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EAWInputComponent.generated.h"

class UInputAction;
class UInputMappingContext;

UENUM()
enum class EInputModifierType : uint8
{
	/* Input values within the range LowerThreshold -> UpperThreshold will be remapped from 0 -> 1. 
	Values outside this range will be clamped. */
	DeadZone,

	/* Apply FOV dependent scaling to input values, per axis */
	FOVScaling,

	/* A user definable group of modifiers that can be easily applied to multiple actions or mappings to save duplication work. */
	ModifierCollection,

	/* Inverts input per axis. */
	Negate,

	/* Apply a simple exponential response curve to input values, per axis. */
	ResponseCurveExponential,

	/* Apply a custom response curve to input values, per axis */
	ResponseCurveUserDefined,

	/* Scales input by a set factor per axis. */
	Scalar,

	/* Smooth inputs out over multiple frames */
	Smooth,

	/* Swizzle axis components of an input value. Useful to map a 1D input onto the Y axis of a 2D action. */
	SwizzleInputAxisValues,

	/* Input space to World space conversion
	Auto-converts axes within the Input Action Value into world space	allowing the result to be directly plugged into functions that take world space values.
	E.g. For a 2D input axis up/down is mapped to world X (forward), whilst axis left/right is mapped to world Y (right). */
	ToWorldSpace
};

UENUM()
enum class EInputTriggerType : uint8
{
	/* Applies a chord action that must be triggering for this trigger's action to trigger */
	ChordedAction,

	/* Trigger fires when the input exceeds the actuation threshold. */
	Down,

	/* Trigger fires once input has remained actuated for HoldTimeThreshold seconds.
	Trigger may optionally fire once, or repeatedly fire. */
	Hold,

	/* Trigger fires when input is released after having been actuated for at least HoldTimeThreshold seconds. */
	HoldAndRelease,

	/* Trigger fires once only when input exceeds the actuation threshold. */
	Pressed,

	/* Trigger that fires at an Interval, in seconds, while input is actuated. */
	Pulse,

	/* Trigger returns Ongoing whilst input exceeds the actuation threshold.
	Trigger fires once only when input drops back below actuation threshold. */
	Released,

	/* Input must be actuated then released within TapReleaseTimeThreshold seconds to trigger. */
	Tap
};

/**
 * Class for Enhanced Input management
 */
UCLASS()
class EMPIREATWARUE5_API UEAWInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE UInputMappingContext* GetMappingContext() const { return PawnMappingContext; };
	FORCEINLINE UInputAction* GetMovementAction() const { return MovementAction; };
	FORCEINLINE UInputAction* GetMouseAction() const { return MouseAction; };
	FORCEINLINE UInputAction* GetZoomAction() const { return ZoomAction; };

protected:
	UEAWInputComponent(const FObjectInitializer& ObjectInitializer);
	virtual void InitializeComponent() override;

	UPROPERTY()
	UInputMappingContext* PawnMappingContext;

	UPROPERTY()
	UInputAction* MovementAction;

	UPROPERTY()
	UInputAction* MouseAction;

	UPROPERTY()
	UInputAction* ZoomAction;
};
