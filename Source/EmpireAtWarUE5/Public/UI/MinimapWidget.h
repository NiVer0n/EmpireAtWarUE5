// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinimapWidget.generated.h"

class UImage;
class UOverlay;
class UMinimapObjectWidget;

UCLASS()
class EMPIREATWARUE5_API UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMinimapObjectWidget* AddObjectToMinimap(const FVector InObjectLocation);

protected:
	UMinimapWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	TObjectPtr<UImage> MinimapImage;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	TObjectPtr<UOverlay> MinimapContainer;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "MinimapSettings")
	TSubclassOf<UMinimapObjectWidget> MinimapObjectWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "MinimapSettings")
	bool bCaptureMinimapBackFromLevel;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MinimapSettings")
	FVector2D MinimapSize;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MinimapSettings")
	FVector2D LevelSize;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "MinimapSettings")
	float MinimapZoomRatio;
};
