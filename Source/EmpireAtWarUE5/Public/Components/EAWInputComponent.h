// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/DA_InputConfig.h"
#include "GameplayTagContainer.h"
#include "EAWInputComponent.generated.h"

class UInputAction;

/**
 * Class for Enhanced Input management
 */
UCLASS()
class EMPIREATWARUE5_API UEAWInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass, typename FuncType>
	void BindActionByTag(const UDA_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
};

template <class UserClass, typename FuncType>
void UEAWInputComponent::BindActionByTag(const UDA_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
};
