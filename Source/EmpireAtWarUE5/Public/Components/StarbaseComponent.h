// NiVeron Games 2023. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "StarbaseComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EMPIREATWARUE5_API UStarbaseComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	void SpawnStarbaseVisual(UStaticMesh* Mesh);
};
