// NiVeron Games 2022. All rights reserved.

#include "Components/EAWInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputModifiers.h"
#include "InputTriggers.h"

static void MapKey(UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key, TArray<EInputTriggerType> TriggerTypes = {}, TArray<EInputModifierType> ModifierTypes = {}, EInputAxisSwizzle SwizzleOrder = EInputAxisSwizzle::YXZ)
{
	FEnhancedActionKeyMapping& Mapping = InputMappingContext->MapKey(InputAction, Key);
	UObject* Outer = InputMappingContext->GetOuter();

	for (EInputModifierType ModifierType : ModifierTypes)
	{
		switch (ModifierType)
		{
			case EInputModifierType::Negate:
			{
				UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(Outer);
				Mapping.Modifiers.Add(Negate);
				break;
			}
			case EInputModifierType::SwizzleInputAxisValues:
			{
				UInputModifierSwizzleAxis* Swizzle = NewObject<UInputModifierSwizzleAxis>(Outer);
				Swizzle->Order = SwizzleOrder;
				Mapping.Modifiers.Add(Swizzle);
				break;
			}
			default: break;
		}
	}

	for (EInputTriggerType TriggerType : TriggerTypes)
	{
		switch (TriggerType)
		{
			case EInputTriggerType::Pressed:
			{
				UInputTriggerPressed* TriggerPressed = NewObject<UInputTriggerPressed>(Outer);
				Mapping.Triggers.Add(TriggerPressed);
				break;
			}
			case EInputTriggerType::Released:
			{
				UInputTriggerReleased* TriggerReleased = NewObject<UInputTriggerReleased>(Outer);
				Mapping.Triggers.Add(TriggerReleased);
				break;
			}
			default: break;
		}
	}
}

UEAWInputComponent::UEAWInputComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bWantsInitializeComponent = true;
}

void UEAWInputComponent::InitializeComponent()
{
	Super::InitializeComponent();

	PawnMappingContext = NewObject<UInputMappingContext>(this);
	
	MovementAction = NewObject<UInputAction>(this);
	MovementAction->ValueType = EInputActionValueType::Axis2D;
	MapKey(PawnMappingContext, MovementAction, EKeys::W, {}, { EInputModifierType::SwizzleInputAxisValues });
	MapKey(PawnMappingContext, MovementAction, EKeys::A, {}, { EInputModifierType::Negate });
	MapKey(PawnMappingContext, MovementAction, EKeys::S, {}, { EInputModifierType::Negate, EInputModifierType::SwizzleInputAxisValues });
	MapKey(PawnMappingContext, MovementAction, EKeys::D);

	MouseAction = NewObject<UInputAction>(this);
	MouseAction->ValueType = EInputActionValueType::Boolean;
	MapKey(PawnMappingContext, MouseAction, EKeys::LeftMouseButton, { EInputTriggerType::Pressed });
	//MapKey(PawnMappingContext, MouseAction, EKeys::RightMouseButton, { EInputTriggerType::Pressed }, { EInputModifierType::Negate });

	ZoomAction = NewObject<UInputAction>(this);
	ZoomAction->ValueType = EInputActionValueType::Axis1D;
	MapKey(PawnMappingContext, ZoomAction, EKeys::MouseWheelAxis);
}
