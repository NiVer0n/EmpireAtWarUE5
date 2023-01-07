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
	AddTag(INPUT_MOVE_TAG, "Input.Move", "Movement input.");
	AddTag(INPUT_ROTATE_TAG, "Input.Rotate", "Rotation input.");
	AddTag(INPUT_ZOOM_TAG, "Input.Zoom", "Zoom input.");
	AddTag(INPUT_SLIDE_TAG, "Input.Slide", "Free slide camera.");
	AddTag(INPUT_SPIN_TAG, "Input.Spin", "Free spin camera.");
	AddTag(INPUT_RESTORE_POSITION_TAG, "Input.RestorePosition", "Restore last saved camera position.");
	AddTag(INPUT_PRIMARY_ACTION_TAG, "Input.PrimaryAction", "Interaction input.");
	// Faction Tags
	AddTag(FACTION_NEUTRAL_TAG, "Faction.Neutral", "Non-playable faction.");
	AddTag(FACTION_EMPIRE_TAG, "Faction.Empire", "Playable faction.");
	AddTag(FACTION_REBELS_TAG, "Faction.Rebels", "Playable faction.");
	AddTag(FACTION_PIRATES_TAG, "Faction.Pirates", "Non-playable faction.");
	// HUD Tags
	AddTag(WIDGETS_MINIMAP_TAG, "HUD.Widgets.Minimap", "Minimap widget.");
	AddTag(WIDGETS_DATA_PANEL_TAG, "HUD.Widgets.DataPanel", "Widget for displaying player's resources, galaxy time control, etc.");

	// Star systems Tags
	AddTag(GAMEPLAY_STARSYSTEM_ABREGADORAE_TAG, "Gameplay.StarSystems.AbregadoRae", "Abregado Rae system");
	AddTag(GAMEPLAY_STARSYSTEM_AETENII_TAG, "Gameplay.StarSystems.AetenII", "Aeten II system");
	AddTag(GAMEPLAY_STARSYSTEM_ALDERAAN_TAG, "Gameplay.StarSystems.Alderaan", "Alderaan system");
	AddTag(GAMEPLAY_STARSYSTEM_ALZOCIII_TAG, "Gameplay.StarSystems.AlzocIII", "Alzoc III system");
	AddTag(GAMEPLAY_STARSYSTEM_ANAXES_TAG, "Gameplay.StarSystems.Anaxes", "Anaxes system");
	AddTag(GAMEPLAY_STARSYSTEM_ATZERRI_TAG, "Gameplay.StarSystems.Atzerri", "Atzerri system");
	AddTag(GAMEPLAY_STARSYSTEM_BESPIN_TAG, "Gameplay.StarSystems.Bespin", "Bespin system");
	AddTag(GAMEPLAY_STARSYSTEM_BESTINE_TAG, "Gameplay.StarSystems.Bestine", "Bestine system");
	AddTag(GAMEPLAY_STARSYSTEM_BONADAN_TAG, "Gameplay.StarSystems.Bonadan", "Bonadan system");
	AddTag(GAMEPLAY_STARSYSTEM_BOTHAWUI_TAG, "Gameplay.StarSystems.Bothawui", "Bothawui system");
	AddTag(GAMEPLAY_STARSYSTEM_BYSS_TAG, "Gameplay.StarSystems.Byss", "Byss system");
	AddTag(GAMEPLAY_STARSYSTEM_CARIDA_TAG, "Gameplay.StarSystems.Carida", "Carida system");
	AddTag(GAMEPLAY_STARSYSTEM_CORELLIA_TAG, "Gameplay.StarSystems.Correlia", "Correlia system");
	AddTag(GAMEPLAY_STARSYSTEM_CORULAG_TAG, "Gameplay.StarSystems.Corulag", "Corulag system");
	AddTag(GAMEPLAY_STARSYSTEM_CORUSCANT_TAG, "Gameplay.StarSystems.Coruscant", "Coruscant system");
	AddTag(GAMEPLAY_STARSYSTEM_DAGOBAH_TAG, "Gameplay.StarSystems.Dagobah", "Dagobah system");
	AddTag(GAMEPLAY_STARSYSTEM_DANTOOINE_TAG, "Gameplay.StarSystems.Dantooine", "Dantooine system");
	AddTag(GAMEPLAY_STARSYSTEM_ENDOR_TAG, "Gameplay.StarSystems.Endor", "Endor system");
	AddTag(GAMEPLAY_STARSYSTEM_ERIADU_TAG, "Gameplay.StarSystems.Eriadu", "Eriadu system");
	AddTag(GAMEPLAY_STARSYSTEM_FONDOR_TAG, "Gameplay.StarSystems.Fondor", "Fondor system");
	AddTag(GAMEPLAY_STARSYSTEM_FRESIA_TAG, "Gameplay.StarSystems.Fresia", "Fresia system");
	AddTag(GAMEPLAY_STARSYSTEM_GEONOSIS_TAG, "Gameplay.StarSystems.Geonosis", "Geonosis system");
	AddTag(GAMEPLAY_STARSYSTEM_HOTH_TAG, "Gameplay.StarSystems.Hoth", "Hoth system");
	AddTag(GAMEPLAY_STARSYSTEM_ILUM_TAG, "Gameplay.StarSystems.Ilum", "Ilum system");
	AddTag(GAMEPLAY_STARSYSTEM_JABIIM_TAG, "Gameplay.StarSystems.Jabiim", "Jabiim system");
	AddTag(GAMEPLAY_STARSYSTEM_KAMINO_TAG, "Gameplay.StarSystems.Kamino", "Kamino system");
	AddTag(GAMEPLAY_STARSYSTEM_KASHYYYK_TAG, "Gameplay.StarSystems.Kashyyyk", "Kashyyyk system");
	AddTag(GAMEPLAY_STARSYSTEM_KESSEL_TAG, "Gameplay.StarSystems.Kessel", "Kessel system");
	AddTag(GAMEPLAY_STARSYSTEM_KORRIBAN_TAG, "Gameplay.StarSystems.Korriban", "Korriban system");
	AddTag(GAMEPLAY_STARSYSTEM_KUAT_TAG, "Gameplay.StarSystems.Kuat", "Kuat system");
	AddTag(GAMEPLAY_STARSYSTEM_MANAAN_TAG, "Gameplay.StarSystems.Manaan", "Manaan system");
	AddTag(GAMEPLAY_STARSYSTEM_MONCALAMARI_TAG, "Gameplay.StarSystems.MonCalamari", "MonCalamari system");
	AddTag(GAMEPLAY_STARSYSTEM_NABOO_TAG, "Gameplay.StarSystems.Naboo", "Naboo system");
	AddTag(GAMEPLAY_STARSYSTEM_NALHUTTA_TAG, "Gameplay.StarSystems.NalHutta", "NalHutta system");
	AddTag(GAMEPLAY_STARSYSTEM_POLUS_TAG, "Gameplay.StarSystems.Polus", "Polus system");
	AddTag(GAMEPLAY_STARSYSTEM_RYLOTH_TAG, "Gameplay.StarSystems.Ryloth", "Ryloth system");
	AddTag(GAMEPLAY_STARSYSTEM_SHOLA_TAG, "Gameplay.StarSystems.Shola", "Shola system");
	AddTag(GAMEPLAY_STARSYSTEM_SULLUST_TAG, "Gameplay.StarSystems.Sullust", "Sullust system");
	AddTag(GAMEPLAY_STARSYSTEM_TARIS_TAG, "Gameplay.StarSystems.Taris", "Taris system");
	AddTag(GAMEPLAY_STARSYSTEM_TATOOINE_TAG, "Gameplay.StarSystems.Tatooine", "Tatooine system");
	AddTag(GAMEPLAY_STARSYSTEM_THYFERRA_TAG, "Gameplay.StarSystems.Thyferra", "Thyferra system");
	AddTag(GAMEPLAY_STARSYSTEM_VERGESSO_TAG, "Gameplay.StarSystems.Vergesso", "Vergesso asteroids system");
	AddTag(GAMEPLAY_STARSYSTEM_WAYLAND_TAG, "Gameplay.StarSystems.Wayland", "Wayland system");
	AddTag(GAMEPLAY_STARSYSTEM_YAVINIV_TAG, "Gameplay.StarSystems.YavinIV", "Yavin IV system");
}

void FEAWGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}