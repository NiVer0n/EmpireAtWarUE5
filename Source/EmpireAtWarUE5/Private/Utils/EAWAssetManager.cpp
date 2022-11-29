// NiVeron Games 2022. All rights reserved.

#include "Utils/EAWAssetManager.h"
#include "Utils/EAWGameplayTags.h"

UEAWAssetManager& UEAWAssetManager::Get()
{
	check(GEngine);

	UEAWAssetManager* EAWAssetManager = Cast<UEAWAssetManager>(GEngine->AssetManager);
	return *EAWAssetManager;
}

void UEAWAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FEAWGameplayTags::InitializeNativeTags();
}