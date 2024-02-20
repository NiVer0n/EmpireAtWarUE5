// NiVeron Games 2022. All rights reserved.

#include "Components/NameComponent.h"
#include "UI/NameWidget.h"

UNameComponent::UNameComponent()
{
	SetWidgetClass(TSubclassOf<UNameWidget>());
}

void UNameComponent::BeginPlay()
{
	Super::BeginPlay();

	NameWidget = Cast<UNameWidget>(GetUserWidgetObject());
}

void UNameComponent::SetName(FText InName)
{
	if (NameWidget && NameWidget->TextBlock)
	{
		NameWidget->TextBlock->SetText(InName);
	}
}

void UNameComponent::SetNameColor(FColor InColor)
{
	if (NameWidget)
	{
		NameWidget->TextBlock->SetColorAndOpacity(FSlateColor(InColor));
	}
}

void UNameComponent::UpdateWidget()
{
	if (!NameWidget)
	{
		NameWidget = Cast<UNameWidget>(GetUserWidgetObject());
	}

	Super::UpdateWidget();
}
