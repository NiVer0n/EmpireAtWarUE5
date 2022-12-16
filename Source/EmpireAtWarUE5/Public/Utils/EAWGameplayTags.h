// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

#define GEAWGameplayTags (FEAWGameplayTags::Get())

/*
 *	Singleton containing native gameplay tags.
 */
struct FEAWGameplayTags
{
public:
	static const FEAWGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	// Input Tags
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Input", meta = (Categories = "Input"))
	FGameplayTag INPUT_MOVE_TAG;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Input", meta = (Categories = "Input"))
	FGameplayTag INPUT_ROTATE_TAG;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Input", meta = (Categories = "Input"))
	FGameplayTag INPUT_ZOOM_TAG;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Input", meta = (Categories = "Input"))
	FGameplayTag INPUT_SLIDE_TAG;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Input", meta = (Categories = "Input"))
	FGameplayTag INPUT_SPIN_TAG;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Input", meta = (Categories = "Input"))
	FGameplayTag INPUT_RESTORE_POSITION_TAG;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Input", meta = (Categories = "Input"))
	FGameplayTag INPUT_PRIMARY_ACTION_TAG;

	// Faction Tags
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Faction", meta = (Categories = "Faction"))
	FGameplayTag FACTION_NEUTRAL_TAG;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Faction", meta = (Categories = "Faction"))
	FGameplayTag FACTION_EMPIRE_TAG;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Faction", meta = (Categories = "Faction"))
	FGameplayTag FACTION_REBELS_TAG;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Faction", meta = (Categories = "Faction"))
	FGameplayTag FACTION_PIRATES_TAG;

	// HUD Tags
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Widges", meta = (Categories = "HUD"))
	FGameplayTag WIDGETS_MINIMAP_TAG;

protected:
	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:
	static FEAWGameplayTags GameplayTags;
};
