// NiVeron Games 2022. All rights reserved.

#include "Engine/LazyLoadWidgetPoint.h"
#include "Editor/WidgetCompilerLog.h"
#include "Misc/UObjectToken.h"

TSharedRef<SWidget> ULazyLoadWidgetPoint::RebuildWidget()
{
	if (IsDesignTime())
	{
		auto GetWidgetPointText = [this]() {
			return FText::FromString("Widget Point\n{0}"), FText::FromName(WidgetPointTag.GetTagName());
		};

		TSharedRef<SOverlay> MessageBox = SNew(SOverlay);

		MessageBox->AddSlot()
			.Padding(5.0f)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
				[SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.Text_Lambda(GetWidgetPointText)];

		return MessageBox;
	}
	else
	{
		return Super::RebuildWidget();
	}
}

#if WITH_EDITOR
void ULazyLoadWidgetPoint::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		if (!WidgetPointTag.IsValid())
		{
			TSharedRef<FTokenizedMessage> Message = CompileLog.Error(
			FText::Format(FText::FromString(
				"{0} has no WidgetPointTag specified - All widget points must specify a tag so they can be located."),
				FText::FromString(GetName())));
			Message->AddToken(FUObjectToken::Create(this));
		}
	}
}
#endif