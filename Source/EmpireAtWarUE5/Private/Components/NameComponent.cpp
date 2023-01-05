// NiVeron Games 2022. All rights reserved.

#include "Components/NameComponent.h"
#include "Components/FactionComponent.h"
#include "UI/NameWidget.h"

UNameComponent::UNameComponent()
{
	SetWidgetClass(TSubclassOf<UNameWidget>());
}

void UNameComponent::BeginPlay()
{
	Super::BeginPlay();

	NameWidget = CastChecked<UNameWidget>(GetUserWidgetObject());
	FactionComponent = GetOwner()->FindComponentByClass<UFactionComponent>();
	if (IsValid(FactionComponent))
	{
		FactionComponent->OnFactionControlChanged.AddDynamic(this, &UNameComponent::ReloadNameColor);
	}
}

void UNameComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(FactionComponent))
	{
		FactionComponent->OnFactionControlChanged.RemoveDynamic(this, &UNameComponent::ReloadNameColor);
	}

	Super::EndPlay(EndPlayReason);
}

void UNameComponent::SetName(FText InName)
{
	NameWidget->GetTextBlock()->SetText(InName);
}

void UNameComponent::SetNameColor(FColor InColor)
{
	NameWidget->GetTextBlock()->SetColorAndOpacity(FSlateColor(InColor));
}

void UNameComponent::ReloadNameColor()
{
	if (IsValid(FactionComponent))
	{
		SetNameColor(FactionComponent->GetFactionColorForPlayer(0));
	}
}