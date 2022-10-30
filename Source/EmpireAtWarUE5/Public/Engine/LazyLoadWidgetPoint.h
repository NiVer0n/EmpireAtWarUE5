// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicEntryBoxBase.h"
#include "GameplayTagContainer.h"
#include "LazyLoadWidgetPoint.generated.h"

/**
 * A slot that defines a location in a layout, where content can be added later
 */
UCLASS()
class EMPIREATWARUE5_API ULazyLoadWidgetPoint : public UDynamicEntryBoxBase
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
#endif
	FORCEINLINE FGameplayTag GetWidgetPointTag() const { return WidgetPointTag; }

	template <typename WidgetT = UUserWidget>
	WidgetT* CreateEntry(const TSubclassOf<WidgetT>& EntryClass = nullptr)
	{
		if (EntryClass && EntryClass->IsChildOf(WidgetT::StaticClass()) && IsEntryClassValid(EntryClass))
		{
			return Cast<WidgetT>(CreateEntryInternal(EntryClass));
		}
		return nullptr;
	}

protected:
	/** The tag that defines this extension point */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LazyLoadWidgetSettings")
	FGameplayTag WidgetPointTag;
};
