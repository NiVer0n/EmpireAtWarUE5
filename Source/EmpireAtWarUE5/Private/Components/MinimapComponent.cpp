// NiVeron Games 2022. All rights reserved.

#include "Components/MinimapComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EAWHUDBase.h"
#include "UI/MinimapWidget.h"
#include "UI/MinimapObjectWidget.h"
#include "Utils/EAWGameplayTags.h"

UMinimapComponent::UMinimapComponent()
	: MinimapWidget(nullptr)
	, PinnedMinimapObjectWidget(nullptr)
	, MinimapIconTexture(nullptr)
	, MinimapIconMaterial(nullptr)
	, MinimapIconMaterialInstance(nullptr)
{
}

void UMinimapComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateMinimapWidget();
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

	MinimapIconMaterialInstance = UMaterialInstanceDynamic::Create(MinimapIconMaterial, this);
	MinimapIconMaterialInstance->SetTextureParameterValue(TEXT("Icon"), MinimapIconTexture);
	PinnedMinimapObjectWidget = MinimapWidget->AddObjectToMinimap(GetOwner()->GetActorLocation());
	PinnedMinimapObjectWidget->UpdateIcon(MinimapIconMaterialInstance);
}

void UMinimapComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(MinimapWidget))
	{
		MinimapWidget->RemoveFromParent();
	}
}

void UMinimapComponent::ReloadMinimapIcon(FColor IconColor)
{
	MinimapIconMaterialInstance->SetVectorParameterValue(TEXT("Color"), IconColor);
}