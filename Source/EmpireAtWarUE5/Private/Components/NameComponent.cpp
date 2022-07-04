// NiVeron Games 2022. All rights reserved.

#include "Components/NameComponent.h"
#include "UI/NameWidget.h"

UNameComponent::UNameComponent()
{
	SetWidgetClass(TSubclassOf<UNameWidget>());
}