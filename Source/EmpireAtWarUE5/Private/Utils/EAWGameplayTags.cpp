// NiVeron Games 2022. All rights reserved.

#include "Utils/EAWGameplayTags.h"
#include "GameplayTagsManager.h"
#include "Engine/EngineTypes.h"

FEAWGameplayTags FEAWGameplayTags::GameplayTags;

void FEAWGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

void FEAWGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(INPUT_MOVE_TAG, "InputTag.Move", "Move input.");
	AddTag(INPUT_PRIMARY_ACTION_TAG, "InputTag.PrimaryAction", "Interaction input.");
	AddTag(INPUT_ZOOM_TAG, "InputTag.Zoom", "Look (stick) input.");
}

void FEAWGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}