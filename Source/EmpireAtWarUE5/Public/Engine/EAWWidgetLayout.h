// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "EAWWidgetLayout.generated.h"

/**
 * Every widget in this map will be created and added to HUD on game started,
 * if UHUDWidget has LazyLoadWidgetPoint with matched tag.
 */
UCLASS()
class EMPIREATWARUE5_API UEAWWidgetLayout : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE const TMap<TSoftClassPtr<UUserWidget>, FGameplayTag>& GetWidgetLayoutData() const { return LayoutData; };

protected:
	UPROPERTY(EditAnywhere, meta = (Categories = "HUD.Widgets"))
	TMap<TSoftClassPtr<UUserWidget>, FGameplayTag> LayoutData;
};
