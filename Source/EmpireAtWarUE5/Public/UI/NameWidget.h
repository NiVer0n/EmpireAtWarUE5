// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NameWidget.generated.h"

/**
 * 
 */
UCLASS()
class EMPIREATWARUE5_API UNameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetName(FText Name) { TextBlock->SetText(Name); };

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextBlock;
};
