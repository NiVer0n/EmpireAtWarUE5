// NiVeron Games 2022. All rights reserved.

#include "Subsystems/ConsumableResourcesSubsystem.h"

bool UConsumableResourcesSubsystem::ConsumeResource(const EResourceTypes ResourceType, int32 Amount)
{
	const int32 CurrentAmount = *ConsumableResources.Find(ResourceType);
	if (CurrentAmount && CurrentAmount - Amount < 0)
	{
		return false;
	}

	ConsumableResources.Emplace(ResourceType, CurrentAmount - Amount);
	OnResourcesChanged.Broadcast(ResourceType, CurrentAmount - Amount);
	return true;
}

void UConsumableResourcesSubsystem::AddConsumableResource(const EResourceTypes ResourceType, int32 Amount)
{
	const int32 CurrentAmount = ConsumableResources.FindOrAdd(ResourceType);
	ConsumableResources.Emplace(ResourceType, CurrentAmount + Amount);
	OnResourcesChanged.Broadcast(ResourceType, CurrentAmount + Amount);
}
