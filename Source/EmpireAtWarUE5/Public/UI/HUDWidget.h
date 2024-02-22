// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

struct FGameplayTag;

/**
 * Widget used to lay out the player's HUD
 */
UCLASS()
class EMPIREATWARUE5_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CanvasPanel;

public:
	UUserWidget* CreateWidgetAtSuitablePoint(const TSoftClassPtr<UUserWidget> WidgetClass, const FGameplayTag WidgetPointTag);
};
