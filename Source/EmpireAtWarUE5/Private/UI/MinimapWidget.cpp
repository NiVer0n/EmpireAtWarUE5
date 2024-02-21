// NiVeron Games 2022. All rights reserved.

#include "UI/MinimapWidget.h"
#include "UI/MinimapObjectWidget.h"
#include "Components/Overlay.h"
#include "Components/MinimapComponent.h"
#include "Components/Image.h"
#include "Engine/SceneCapture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/CameraBoundsVolume.h"

UMinimapWidget::UMinimapWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bCaptureMinimapBackFromLevel(true)
	, MinimapSize(FVector2D())
	, LevelSize(FVector2D())
	, MinimapZoomRatio(2.0f)
{
}

void UMinimapWidget::NativeConstruct()
{
	if (bCaptureMinimapBackFromLevel)
	{
		ASceneCapture2D* SceneCapture = Cast<ASceneCapture2D>(UGameplayStatics::GetActorOfClass(GetWorld(), ASceneCapture2D::StaticClass()));
		check(SceneCapture);
		/* Captured texture (RT_MinimapCapture) after this applies to M_MinimapCapture material */
		SceneCapture->GetCaptureComponent2D()->CaptureScene();
	}
	const ACameraBoundsVolume* CameraBoundsActor = Cast<ACameraBoundsVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraBoundsVolume::StaticClass()));
	check(IsValid(CameraBoundsActor));

	FVector Origin, BoxExtend;
	CameraBoundsActor->GetActorBounds(false, Origin, BoxExtend);
	LevelSize = FVector2D(BoxExtend * MinimapZoomRatio);
	MinimapSize = MinimapImage->GetBrush().ImageSize;
}

UMinimapObjectWidget* UMinimapWidget::AddObjectToMinimap(const FVector InObjectLocation)
{
	UMinimapObjectWidget* ObjectWidget = CreateWidget<UMinimapObjectWidget>(this, MinimapObjectWidgetClass);
	check(ObjectWidget);
	MinimapContainer->AddChild(ObjectWidget);

	const FVector2D ObjectNormalizedLocation = FVector2D(InObjectLocation.Y / LevelSize.Y, InObjectLocation.X / LevelSize.X * -1.0f) + 0.5f;
	const FVector2D ObjectPosition = FVector2D(ObjectNormalizedLocation.X * MinimapSize.X, ObjectNormalizedLocation.Y * MinimapSize.Y);
	ObjectWidget->SetRenderTranslation(ObjectPosition);
	return ObjectWidget;
}
