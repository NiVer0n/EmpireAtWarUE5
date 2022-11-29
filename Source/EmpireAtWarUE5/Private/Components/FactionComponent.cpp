// NiVeron Games 2022. All rights reserved.

#include "Components/FactionComponent.h"
#include "Engine/EAWSettings.h"
#include "Data/DA_Factions.h"
#include "Player/EAWPlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

UFactionComponent::UFactionComponent()
	: FactionsDataAsset(nullptr)
	, OwnerFactionTag(FGameplayTag())
{ }

void UFactionComponent::BeginPlay()
{
	Super::BeginPlay();

	FactionsDataAsset = GEAWSettings.GetFactionsDataAsset();
	checkf(FactionsDataAsset, TEXT("%s: FactionsDataAsset is invalid."), ANSI_TO_TCHAR(__FUNCTION__));
	OnFactionControlChanged.AddDynamic(this, &UFactionComponent::SetOwnerFactionTag);
}

void UFactionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnFactionControlChanged.RemoveDynamic(this, &UFactionComponent::SetOwnerFactionTag);
}

FColor UFactionComponent::GetFactionColor() const
{
	const AEAWPlayerControllerBase* PC = Cast<AEAWPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!IsValid(PC))
	{
		return FColor::White;
	}

	const FGameplayTag PlayerTag = PC->GetFactionComponent()->GetOwnerFactionTag();
	if (OwnerFactionTag.MatchesTagExact(PlayerTag))
	{
		return FactionsDataAsset->GetAllyColor();
	}

	const FFactionsData* SourceFactionData = FactionsDataAsset->GetFactionsData().Find(OwnerFactionTag);
	if (SourceFactionData && PlayerTag.MatchesTagExact(SourceFactionData->PrimaryEnemy))
	{
		return FactionsDataAsset->GetEnemyColor();
	}
	return SourceFactionData->Color;
}