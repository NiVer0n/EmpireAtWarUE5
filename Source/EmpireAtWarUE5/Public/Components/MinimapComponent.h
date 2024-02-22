// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MinimapComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EMPIREATWARUE5_API UMinimapComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ReloadMinimapIcon(FColor IconColor);

protected:
	UMinimapComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
	TObjectPtr<class UMinimapWidget> MinimapWidget;

	UPROPERTY()
	TObjectPtr<class UMinimapObjectWidget> PinnedMinimapObjectWidget;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "MinimapSettings")
	TObjectPtr<class UTexture2D> MinimapIconTexture;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "MinimapSettings")
	TObjectPtr<class UMaterial> MinimapIconMaterial;

private:
	void CreateMinimapWidget();

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MinimapIconMaterialInstance;
};
