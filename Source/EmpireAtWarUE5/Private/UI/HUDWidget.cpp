// NiVeron Games 2022. All rights reserved.

#include "UI/HUDWidget.h"
#include "Components/CanvasPanel.h"
#include "Engine/LazyLoadWidgetPoint.h"
#include "GameplayTagContainer.h"

UUserWidget* UHUDWidget::CreateWidgetAtSuitablePoint(const TSoftClassPtr<UUserWidget> WidgetClass, const FGameplayTag WidgetPointTag)
{
	for (UWidget* Widget : CanvasPanel->GetAllChildren())
	{
		ULazyLoadWidgetPoint* WidgetPoint = Cast<ULazyLoadWidgetPoint>(Widget);
		if (WidgetPoint && WidgetPoint->GetWidgetPointTag() == WidgetPointTag)
		{
			return WidgetPoint->CreateEntry<UUserWidget>(WidgetClass.LoadSynchronous());
		}
	}
	ensureMsgf(false, TEXT("%s: widget with tag %s not found in HUDWidget"), ANSI_TO_TCHAR(__FUNCTION__), *WidgetPointTag.GetTagName().ToString());
	return nullptr;
}