// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Subsystems/ConsumableResourcesSubsystem.h"
#include "DataPanelWidget.generated.h"

/**
 * Class representing gameplay data: e.g. player resources, galaxy time control, etc.
 */
UCLASS()
class EMPIREATWARUE5_API UDataPanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void RefreshResourceData(const EResourceTypes ResourceType, int32 Amount);

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UTextBlock* CreditsCountText;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UTextBlock* PopulationCountText;

private:
	void HandleResourceChangedBindings(bool InBinded);
};
