// Copyright Epic Games, Inc. All Rights Reserved.

#include "EmpireAtWarUE5.h"
#include "Modules/ModuleManager.h"
#include "GenericTeamAgentInterface.h"
#include "Engine/EAWSettings.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FEmpireAtWarUE5GameModule, EmpireAtWarUE5, "EmpireAtWarUE5");

namespace
{
	ETeamAttitude::Type DefaultEmpireAtWarUE5TeamAttitudeSolver(FGenericTeamId A, FGenericTeamId B)
	{
		UDA_Factions* FactionsDataAsset = GEAWSettings.GetFactionsDataAsset();
		if (IsValid(FactionsDataAsset) && (FactionsDataAsset->IsNeutral(A) || FactionsDataAsset->IsNeutral(B)))
		{
			return ETeamAttitude::Neutral;
		}

		return FactionsDataAsset->IsAlly(A, B) ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
	}
}

void FEmpireAtWarUE5GameModule::StartupModule()
{
	UE_LOG(LogInit, Display, TEXT("%s"), ANSI_TO_TCHAR(__FUNCTION__));

	FGenericTeamId::SetAttitudeSolver(DefaultEmpireAtWarUE5TeamAttitudeSolver);
}

void FEmpireAtWarUE5GameModule::ShutdownModule()
{
	UE_LOG(LogExit, Display, TEXT("%s"), ANSI_TO_TCHAR(__FUNCTION__));

	FGenericTeamId::ResetAttitudeSolver();
}