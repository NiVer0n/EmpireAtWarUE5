// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinimapObjectWidget.generated.h"

class UImage;
class UOverlay;
class UMaterialInterface;

/**
 * Represents MinimapComponent's owner in minimap widget
 */
UCLASS()
class EMPIREATWARUE5_API UMinimapObjectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateIcon(UMaterialInterface* InIconMaterial);

protected:
	UMinimapObjectWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	TObjectPtr<UOverlay> MinimapIconContainer;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	TObjectPtr<UImage> MinimapIconImage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "MinimapSettings")
	FVector2D IconSize;
};
