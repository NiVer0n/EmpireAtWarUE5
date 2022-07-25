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

	NameWidget = CastChecked<UNameWidget>(GetUserWidgetObject());
}

void UNameComponent::SetName(FText InName)
{
	NameWidget->GetTextBlock()->SetText(InName);
}

void UNameComponent::SetNameColor(FColor InColor)
{
	NameWidget->GetTextBlock()->SetColorAndOpacity(FSlateColor(InColor));
}