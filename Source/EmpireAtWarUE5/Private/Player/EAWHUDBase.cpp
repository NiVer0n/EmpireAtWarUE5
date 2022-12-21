// NiVeron Games 2022. All rights reserved.

#include "Player/EAWHUDBase.h"
#include "UI/HUDWidget.h"
#include "Engine/EAWWidgetLayout.h"
#include "Kismet/GameplayStatics.h"

void AEAWHUDBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!GetWorld() || !ensure(IsValid(HUDWidgetClass)))
	{
		return;
	}

	HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();

	const UEAWWidgetLayout* WidgetLayout = WidgetLayoutData.LoadSynchronous();
	for (const auto& [WidgetClass, WidgetTag] : WidgetLayout->GetWidgetLayoutData())
	{
		UUserWidget* CreatedWidget = HUDWidget->CreateWidgetAtSuitablePoint(WidgetClass, WidgetTag);
		CreatedWidgets.Emplace(WidgetTag, CreatedWidget);
	}
}