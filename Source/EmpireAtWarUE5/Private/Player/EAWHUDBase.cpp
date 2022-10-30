// NiVeron Games 2022. All rights reserved.

#include "Player/EAWHUDBase.h"
#include "UI/HUDWidget.h"
#include "Engine/EAWWidgetLayout.h"
#include "Kismet/GameplayStatics.h"

AEAWHUDBase::AEAWHUDBase()
	: HUDWidget(nullptr)
{
}

void AEAWHUDBase::BeginPlay()
{
	if (!GetWorld() || !IsValid(HUDWidgetClass))
	{
		return;
	}

	HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
	check(HUDWidget);
	HUDWidget->AddToViewport();

	const UEAWWidgetLayout* WidgetLayout = WidgetLayoutData.LoadSynchronous();
	for (const TPair<TSoftClassPtr<UUserWidget>, FGameplayTag>& WidgetToCreate : WidgetLayout->GetWidgetLayoutData())
	{
		UUserWidget* CreatedWidget = HUDWidget->CreateWidgetAtSuitablePoint(WidgetToCreate.Key, WidgetToCreate.Value);
		CreatedWidgets.Emplace(WidgetToCreate.Value, CreatedWidget);
	}
}