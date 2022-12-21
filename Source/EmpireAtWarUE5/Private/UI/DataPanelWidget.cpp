// NiVeron Games 2022. All rights reserved.

#include "UI/DataPanelWidget.h"

void UDataPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HandleResourceChangedBindings(true);
}

void UDataPanelWidget::NativeDestruct()
{
	Super::NativeDestruct();

	HandleResourceChangedBindings(false);
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

void UDataPanelWidget::HandleResourceChangedBindings(bool InBinded)
{
	if (!IsValid(GetOwningLocalPlayer()))
	{
		return;
	}

	UConsumableResourcesSubsystem* ResourceSubsystem = GetOwningLocalPlayer()->GetSubsystem<UConsumableResourcesSubsystem>();
	if (InBinded)
	{
		ResourceSubsystem->OnResourcesChanged.AddUniqueDynamic(this, &ThisClass::RefreshResourceData);
	}
	else
	{
		ResourceSubsystem->OnResourcesChanged.RemoveDynamic(this, &ThisClass::RefreshResourceData);
	}
}
