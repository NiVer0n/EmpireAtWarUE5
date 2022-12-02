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
	// Input Tags
	AddTag(INPUT_MOVE_TAG, "Input.Move", "Move input.");
	AddTag(INPUT_PRIMARY_ACTION_TAG, "Input.PrimaryAction", "Interaction input.");
	AddTag(INPUT_ZOOM_TAG, "Input.Zoom", "Zoom input.");
	// Faction Tags
	AddTag(FACTION_NEUTRAL_TAG, "Faction.Neutral", "Non-playable faction.");
	AddTag(FACTION_EMPIRE_TAG, "Faction.Empire", "Playable faction.");
	AddTag(FACTION_REBELS_TAG, "Faction.Rebels", "Playable faction.");
	AddTag(FACTION_PIRATES_TAG, "Faction.Pirates", "Non-playable faction.");
	// HUD Tags
	AddTag(WIDGETS_MINIMAP_TAG, "HUD.Widgets.Minimap", "Minimap widget.");
}

void FEAWGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}