// NiVeron Games 2022. All rights reserved.

#include "Data/DA_InputConfig.h"
#include "InputAction.h"

const UInputAction* UDA_InputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	const auto FoundInputAction = TaggedInputActions.FindByPredicate(
		[&](const FTaggedInputAction& TaggedInputAction) {
			return TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag;
		});

	return FoundInputAction ? FoundInputAction->InputAction : nullptr;
}