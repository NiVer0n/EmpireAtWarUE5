// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "NameComponent.generated.h"

class UNameWidget;
class UFactionComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EMPIREATWARUE5_API UNameComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	void SetName(FText InName);
	void SetNameColor(FColor InColor);

protected:
	UNameComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void ReloadNameColor();

	UPROPERTY()
	UNameWidget* NameWidget;

	UPROPERTY()
	UFactionComponent* FactionComponent;
};