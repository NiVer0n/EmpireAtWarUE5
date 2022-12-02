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

	if (!GetWorld() || !GetOwner())
	{
		return;
	}

	if (const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (AEAWHUDBase* HUD = Cast<AEAWHUDBase>(PC->GetHUD()))
		{
			MinimapWidget = HUD->GetDesiredWidget<UMinimapWidget>(GEAWGameplayTags.WIDGETS_MINIMAP_TAG);
			if (IsValid(MinimapWidget))
			{
				PinnedMinimapObjectWidget = MinimapWidget->AddObjectToMinimap(GetOwner()->GetActorLocation());
				PinnedMinimapObjectWidget->UpdateIcon(CreateIconFromData());
			}
		}
	}

	FactionComponent = GetOwner()->FindComponentByClass<UFactionComponent>();
	if (IsValid(FactionComponent))
	{
		FactionComponent->OnFactionControlChanged.AddDynamic(this, &UMinimapComponent::ReloadMinimapIcon);
	}
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
		MinimapIconMaterialInstance->SetVectorParameterValue(TEXT("Color"), FactionComponent->GetFactionColor());
	}
	return MinimapIconMaterialInstance;
}

void UMinimapComponent::ReloadMinimapIcon(FGameplayTag NewOwnerFactionTag)
{
	if (IsValid(PinnedMinimapObjectWidget))
	{
		PinnedMinimapObjectWidget->UpdateIcon(CreateIconFromData());
	}
}