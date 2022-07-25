// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Zoomable.generated.h"

UINTERFACE(MinimalAPI)
class UZoomable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EMPIREATWARUE5_API IZoomable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Zoom")
	void ZoomToObject(bool IsZoomIn);
	virtual void ZoomToObject_Implementation(bool IsZoomIn);
};
