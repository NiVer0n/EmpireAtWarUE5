// NiVeron Games 2022. All rights reserved.

#include "UI/DataPanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/Progressbar.h"
#include "Components/Button.h"
#include "Subsystems/GalaxyTimeSubsystem.h"
#include "Player/EAWPlayerControllerBase.h"

void UDataPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HandleBindings(true);
}

void UDataPanelWidget::NativeDestruct()
{
	Super::NativeDestruct();

	HandleBindings(false);
}

void UDataPanelWidget::HandleBindings(bool InBinded)
{
	const ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	if (!IsValid(LocalPlayer))
	{
		return;
	}

	UConsumableResourcesSubsystem* ResourceSubsystem = LocalPlayer->GetSubsystem<UConsumableResourcesSubsystem>();
	UGalaxyTimeSubsystem* GalaxyTimeSubsystem = LocalPlayer->GetWorld()->GetSubsystem<UGalaxyTimeSubsystem>();
	if (InBinded)
	{
		ResourceSubsystem->OnResourcesChanged.AddUniqueDynamic(this, &ThisClass::RefreshResourceData);
		GalaxyTimeSubsystem->OnGalaxyTimeChanged.AddUniqueDynamic(this, &ThisClass::UpdateCurrentDayProgressBar);
		GalaxyTimeSubsystem->OnGalaxyDayChanged.AddUniqueDynamic(this, &ThisClass::UpdateCurrentDayText);
		PauseGameButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnPauseGameButtonPressed);
		SpeedUpTimeButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnSpeedUpTimeButtonPressed);
	}
	else
	{
		ResourceSubsystem->OnResourcesChanged.RemoveDynamic(this, &ThisClass::RefreshResourceData);
		GalaxyTimeSubsystem->OnGalaxyTimeChanged.RemoveDynamic(this, &ThisClass::UpdateCurrentDayProgressBar);
		GalaxyTimeSubsystem->OnGalaxyDayChanged.RemoveDynamic(this, &ThisClass::UpdateCurrentDayText);
		PauseGameButton->OnClicked.RemoveDynamic(this, &ThisClass::OnPauseGameButtonPressed);
		SpeedUpTimeButton->OnClicked.RemoveDynamic(this, &ThisClass::OnSpeedUpTimeButtonPressed);
	}
}

void UDataPanelWidget::OnPauseGameButtonPressed()
{
	if (!GetOwningPlayer())
	{
		return;
	}

	AEAWPlayerControllerBase* PC = Cast<AEAWPlayerControllerBase>(GetOwningPlayer());
	if (IsValid(PC))
	{
		PC->ToggleGamePause(true);
	}
}

void UDataPanelWidget::OnSpeedUpTimeButtonPressed()
{
	if (!GetOwningPlayer())
	{
		return;
	}

	AEAWPlayerControllerBase* PC = Cast<AEAWPlayerControllerBase>(GetOwningPlayer());
	if (IsValid(PC))
	{
		PC->ToggleGameSpeed();
	}
}

void UDataPanelWidget::RefreshResourceData(const EResourceTypes ResourceType, int32 Amount)
{
	switch (ResourceType)
	{
		case EResourceTypes::None: break;
		case EResourceTypes::Credits:
		{
			CreditsCountText->SetText(FText::AsNumber(Amount));
			break;
		}
		case EResourceTypes::Population:
		{
			PopulationCountText->SetText(FText::AsNumber(Amount));
			break;
		}
		default: break;
	}
}

void UDataPanelWidget::UpdateCurrentDayProgressBar(float InCurrentTime, float InDayDuration)
{
	PB_CurrentDay->SetPercent(FMath::Fmod(InCurrentTime, InDayDuration) / 10.0f);
}

void UDataPanelWidget::UpdateCurrentDayText(int32 InDay)
{
	CurrentDayText->SetText(FText::AsNumber(InDay));
}
