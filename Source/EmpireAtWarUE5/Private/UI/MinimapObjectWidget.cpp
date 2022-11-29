// NiVeron Games 2022. All rights reserved.

#include "UI/MinimapObjectWidget.h"
#include "Components/Image.h"
#include "Components/OverlaySlot.h"
#include "Components/MinimapComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UMinimapObjectWidget::UMinimapObjectWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, IconSize(FVector2D(8.0f))
{
}

void UMinimapObjectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MinimapIconImage->SetDesiredSizeOverride(IconSize);

	const FMargin Margin = FMargin(IconSize.X / 2.0f * -1.0f, IconSize.Y / 2.0f * -1.0f, 0.0f, 0.0f);
	UWidgetLayoutLibrary::SlotAsOverlaySlot(MinimapIconImage)->SetPadding(Margin);
}

void UMinimapObjectWidget::UpdateIcon(UMaterialInterface* InIconMaterial)
{
	MinimapIconImage->SetBrushFromMaterial(InIconMaterial);
}