// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystems/ConsumableResourcesSubsystem.h"
#include "DataPanelWidget.generated.h"

class UTextBlock;
class UProgressBar;
class UButton;
class AActor;

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

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UTextBlock* CreditsCountText;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UTextBlock* TaxCountText;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UTextBlock* SelectedSystemTaxCountText;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UTextBlock* SelectedSystemNameText;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UTextBlock* PopulationCountText;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UProgressBar* PB_CurrentDay;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UTextBlock* CurrentDayText;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UButton* PauseGameButton;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (BindWidget))
	UButton* SpeedUpTimeButton;

private:
	void HandleBindings(bool InBinded);

	UFUNCTION()
	void RefreshResourceData(const EResourceTypes ResourceType, int32 Amount);

	UFUNCTION()
	void UpdateCurrentDayProgressBar(float InCurrentTime, float InDayDuration);

	UFUNCTION()
	void UpdateCurrentDayText(int32 InDay);

	UFUNCTION()
	void UpdateSelectedActorInfo(const AActor* SelectedActor);

	UFUNCTION()
	void UpdateTaxCountText();

	UFUNCTION()
	void OnPauseGameButtonPressed();

	UFUNCTION()
	void OnSpeedUpTimeButtonPressed();
};
