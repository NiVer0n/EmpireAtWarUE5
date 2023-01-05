// NiVeron Games 2022. All rights reserved.

#include "Components/MinimapComponent.h"
#include "Components/FactionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EAWHUDBase.h"
#include "UI/MinimapWidget.h"
#include "UI/MinimapObjectWidget.h"
#include "Utils/EAWGameplayTags.h"

UMinimapComponent::UMinimapComponent()
	: MinimapWidget(nullptr)
	, PinnedMinimapObjectWidget(nullptr)
	, FactionComponent(nullptr)
	, MinimapIconTexture(nullptr)
	, MinimapIconMaterial(nullptr)
{
}

void UMinimapComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateMinimapWidget();
	
	FactionComponent = GetOwner()->FindComponentByClass<UFactionComponent>();
	if (IsValid(FactionComponent))
	{
		FactionComponent->OnFactionControlChanged.AddDynamic(this, &UMinimapComponent::ReloadMinimapIcon);
	}
}

void UMinimapComponent::CreateMinimapWidget()
{
	if (!GetWorld())
	{
		return;
	}

	const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PC))
	{
		return;
	}

	AEAWHUDBase* HUD = Cast<AEAWHUDBase>(PC->GetHUD());
	if (!IsValid(HUD))
	{
		return;
	}

	MinimapWidget = HUD->GetDesiredWidget<UMinimapWidget>(GEAWGameplayTags.WIDGETS_MINIMAP_TAG);
	if (!IsValid(MinimapWidget))
	{
		return;
	}

	PinnedMinimapObjectWidget = MinimapWidget->AddObjectToMinimap(GetOwner()->GetActorLocation());
	PinnedMinimapObjectWidget->UpdateIcon(CreateIconFromData());
}

void UMinimapComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(FactionComponent))
	{
		FactionComponent->OnFactionControlChanged.RemoveDynamic(this, &UMinimapComponent::ReloadMinimapIcon);
	}

	if (IsValid(MinimapWidget))
	{
		MinimapWidget->RemoveFromParent();
	}
}

UMaterialInstanceDynamic* UMinimapComponent::CreateIconFromData()
{
	UMaterialInstanceDynamic* MinimapIconMaterialInstance = UMaterialInstanceDynamic::Create(MinimapIconMaterial, this);
	MinimapIconMaterialInstance->SetTextureParameterValue(TEXT("Icon"), MinimapIconTexture);
	if (IsValid(FactionComponent))
	{
		MinimapIconMaterialInstance->SetVectorParameterValue(TEXT("Color"), FactionComponent->GetFactionColorForPlayer(0));
	}
	return MinimapIconMaterialInstance;
}

void UMinimapComponent::ReloadMinimapIcon()
{
	if (IsValid(PinnedMinimapObjectWidget))
	{
		PinnedMinimapObjectWidget->UpdateIcon(CreateIconFromData());
	}
}