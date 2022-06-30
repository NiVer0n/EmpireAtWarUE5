// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "CameraBoundsVolume.generated.h"

/* 
 * Volume that restricts camera movement.
 * Cameras are not allowed to move outside of this volume.
 * There should never be more than one camera bounds volume per level.
 */
UCLASS()
class EMPIREATWARUE5_API ACameraBoundsVolume : public AVolume
{
	GENERATED_BODY()
};
