// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Selectable.generated.h"

UINTERFACE(MinimalAPI)
class USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class EMPIREATWARUE5_API ISelectable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Selection")
	void SelectObject();
	virtual void SelectObject_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Selection")
	void DeselectObject();
	virtual void DeselectObject_Implementation();
};
