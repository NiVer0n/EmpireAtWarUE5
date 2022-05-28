// NiVeron Games 2022. All rights reserved.

#include "Components/NameComponent.h"

UNameComponent::UNameComponent()
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetRelativeLocationAndRotation(FVector(0.0f, 50.0f, 0.0f), FRotator(0.0f, 0.0f, 180.0f));
}
