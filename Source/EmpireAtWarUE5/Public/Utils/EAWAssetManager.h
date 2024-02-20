// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "EAWAssetManager.generated.h"

/**
 *
 */
UCLASS()
class EMPIREATWARUE5_API UEAWAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// Returns the AssetManager singleton object.
	static UEAWAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
