// NiVeron Games 2022. All rights reserved.

#include "UI/DataPanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/Progressbar.h"
#include "Components/Button.h"
#include "Subsystems/GalaxyTimeSubsystem.h"
#include "Player/EAWPlayerControllerBase.h"
#include "Player/EAWPlayerStateBase.h"
#include "Gameplay/StarSystem.h"
#include "Data/DA_StarSystem.h"

void UDataPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HandleBindings(true);
}

void UDataPanelWidget::NativeDestruct()
{
	HandleBindings(false);

	Super::NativeDestruct();
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

	AEAWPlayerControllerBase* EAWPlayerController = Cast<AEAWPlayerControllerBase>(GetOwningPlayer());
	if (!IsValid(EAWPlayerController))
	{
		return;
	}

	AEAWPlayerStateBase* EAWPlayerState = EAWPlayerController->GetPlayerState<AEAWPlayerStateBase>();
	if (!IsValid(EAWPlayerState))
	{
		return;
	}

	if (InBinded)
	{
		ResourceSubsystem->OnResourcesChanged.AddUniqueDynamic(this, &ThisClass::RefreshResourceData);
		GalaxyTimeSubsystem->OnGalaxyTimeChanged.AddUniqueDynamic(this, &ThisClass::UpdateCurrentDayProgressBar);
		GalaxyTimeSubsystem->OnGalaxyDayChanged.AddUniqueDynamic(this, &ThisClass::UpdateCurrentDayText);
		EAWPlayerController->OnActorSelected.AddUniqueDynamic(this, &ThisClass::UpdateSelectedActorInfo);
		EAWPlayerState->OnControlledSystemsChanged.AddUniqueDynamic(this, &ThisClass::UpdateTaxCountText);
		PauseGameButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnPauseGameButtonPressed);
		SpeedUpTimeButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnSpeedUpTimeButtonPressed);
	}
	else
	{
		ResourceSubsystem->OnResourcesChanged.RemoveDynamic(this, &ThisClass::RefreshResourceData);
		GalaxyTimeSubsystem->OnGalaxyTimeChanged.RemoveDynamic(this, &ThisClass::UpdateCurrentDayProgressBar);
		GalaxyTimeSubsystem->OnGalaxyDayChanged.RemoveDynamic(this, &ThisClass::UpdateCurrentDayText);
		EAWPlayerController->OnActorSelected.RemoveDynamic(this, &ThisClass::UpdateSelectedActorInfo);
		EAWPlayerState->OnControlledSystemsChanged.RemoveDynamic(this, &ThisClass::UpdateTaxCountText);
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

	AEAWPlayerControllerBase* EAWPlayerController = Cast<AEAWPlayerControllerBase>(GetOwningPlayer());
	if (IsValid(EAWPlayerController))
	{
		EAWPlayerController->ToggleGamePause(true);
	}
}

void UDataPanelWidget::OnSpeedUpTimeButtonPressed()
{
	if (!GetOwningPlayer())
	{
		return;
	}

	AEAWPlayerControllerBase* EAWPlayerController = Cast<AEAWPlayerControllerBase>(GetOwningPlayer());
	if (IsValid(EAWPlayerController))
	{
		EAWPlayerController->ToggleGameSpeed();
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

void UDataPanelWidget::UpdateSelectedActorInfo(const AActor* SelectedActor)
{
	const bool ActorSelected = IsValid(SelectedActor);
	SelectedSystemTaxCountText->SetVisibility(ActorSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	SelectedSystemNameText->SetVisibility(ActorSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (!ActorSelected)
	{
		return;
	}

	const AStarSystem* StarSystem = Cast<AStarSystem>(SelectedActor);
	if (!IsValid(StarSystem))
	{
		return;
	}

	const UDA_StarSystem* Data = StarSystem->GetStarSystemData();
	if (!Data)
	{
		return;
	}

	SelectedSystemTaxCountText->SetText(FText::AsNumber(Data->TaxAmount));
	SelectedSystemNameText->SetText(Data->Name);
	if (StarSystem->Implements<UFactions>())
	{
		SelectedSystemTaxCountText->SetColorAndOpacity(IFactions::Execute_GetOwnerFactionColor(StarSystem, 0));
		SelectedSystemNameText->SetColorAndOpacity(IFactions::Execute_GetOwnerFactionColor(StarSystem, 0));
	}
}

void UDataPanelWidget::UpdateTaxCountText()
{
	AEAWPlayerStateBase* EAWPlayerState = GetOwningPlayer()->GetPlayerState<AEAWPlayerStateBase>();
	if (!IsValid(EAWPlayerState))
	{
		return;
	}

	int32 TaxAmount = 0;
	for (const AStarSystem* StarSystem : EAWPlayerState->GetControlledStarSystems())
	{
		const UDA_StarSystem* Data = StarSystem->GetStarSystemData();
		if (Data)
		{
			TaxAmount += Data->TaxAmount;
		}
	}

	TaxCountText->SetText(FText::AsNumber(TaxAmount));
}
