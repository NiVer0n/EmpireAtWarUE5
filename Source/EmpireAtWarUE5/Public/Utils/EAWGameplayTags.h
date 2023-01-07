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

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Widges", meta = (Categories = "HUD"))
	FGameplayTag WIDGETS_DATA_PANEL_TAG;

	// Star systems Tags
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_ABREGADORAE_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_AETENII_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_ALDERAAN_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_ALZOCIII_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_ANAXES_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_ATZERRI_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_BESPIN_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_BESTINE_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_BONADAN_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_BOTHAWUI_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_BYSS_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_CARIDA_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_CORELLIA_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_CORULAG_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_CORUSCANT_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_DAGOBAH_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_DANTOOINE_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_ENDOR_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_ERIADU_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_FONDOR_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_FRESIA_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_GEONOSIS_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_HOTH_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_ILUM_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_JABIIM_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_KAMINO_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_KASHYYYK_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_KESSEL_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_KORRIBAN_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_KUAT_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_MANAAN_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_MONCALAMARI_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_NABOO_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_NALHUTTA_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_POLUS_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_RYLOTH_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_SHOLA_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_SULLUST_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_TARIS_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_TATOOINE_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_THYFERRA_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_VERGESSO_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_WAYLAND_TAG;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Tags|Gameplay", meta = (Categories = "Gameplay|StarSystems"))
	FGameplayTag GAMEPLAY_STARSYSTEM_YAVINIV_TAG;

protected:
	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:
	static FEAWGameplayTags GameplayTags;
};
