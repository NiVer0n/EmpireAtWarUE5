// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayTagContainer.h"
#include "EAWHUDBase.generated.h"

class UHUDWidget;
class UEAWWidgetLayout;

UCLASS()
class EMPIREATWARUE5_API AEAWHUDBase : public AHUD
{
	GENERATED_BODY()

public:
	FORCEINLINE const TMap<FGameplayTag, TObjectPtr<UUserWidget>>& GetCreatedWidgets() const { return CreatedWidgets; }

	template <typename WidgetT = UUserWidget>
	WidgetT* GetDesiredWidget(const FGameplayTag DesiredWidgetTag)
	{
		if (DesiredWidgetTag.IsValid() && CreatedWidgets.Contains(DesiredWidgetTag))
		{
			UUserWidget* FoundWidget = CreatedWidgets[DesiredWidgetTag];
			if (IsValid(FoundWidget))
			{
				return Cast<WidgetT>(FoundWidget);
			}
		}
		return nullptr;
	}

protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets")
	TSoftObjectPtr<UEAWWidgetLayout> WidgetLayoutData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets")
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<UHUDWidget> HUDWidget;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UUserWidget>> CreatedWidgets;
};
