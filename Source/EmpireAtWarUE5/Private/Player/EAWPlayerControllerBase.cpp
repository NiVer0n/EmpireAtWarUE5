// NiVeron Games 2022. All rights reserved.

#include "Player/EAWPlayerControllerBase.h"
#include "Components/EAWInputComponent.h"
#include "Utils/EAWGameplayTags.h"
#include "InputTriggers.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Interfaces/Selectable.h"
#include "Components/FactionComponent.h"
#include "Engine/EAWSettings.h"
#include "Kismet/KismetMathLibrary.h"

AEAWPlayerControllerBase::AEAWPlayerControllerBase()
	: PlayerPawn(nullptr)
	, SelectedActors()
	, SelectionStartPoint(FVector2D::ZeroVector)
{
	FactionComponent = CreateDefaultSubobject<UFactionComponent>("FactionComponent");
	// @TODO: Remove this when implementing faction choise
	FactionComponent->SetOwnerFactionTag(GEAWGameplayTags.FACTION_EMPIRE_TAG);
}

void AEAWPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	check(GEAWSettings.GetInputConfigAsset());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(GEAWSettings.GetInputConfigAsset()->GetMappingContext(), 0);

	UEAWInputComponent* EAWInputComponent = Cast<UEAWInputComponent>(InputComponent);
	check(EAWInputComponent);
	EAWInputComponent->BindActionByTag(GEAWSettings.GetInputConfigAsset(), GEAWGameplayTags.INPUT_MOVE_TAG, ETriggerEvent::Triggered, this, &ThisClass::EnhancedMove);
	EAWInputComponent->BindActionByTag(GEAWSettings.GetInputConfigAsset(), GEAWGameplayTags.INPUT_ROTATE_TAG, ETriggerEvent::Triggered, this, &ThisClass::EnhancedRotate);
	EAWInputComponent->BindActionByTag(GEAWSettings.GetInputConfigAsset(), GEAWGameplayTags.INPUT_ZOOM_TAG, ETriggerEvent::Triggered, this, &ThisClass::EnhancedZoom);
	EAWInputComponent->BindActionByTag(GEAWSettings.GetInputConfigAsset(), GEAWGameplayTags.INPUT_SLIDE_TAG, ETriggerEvent::Triggered, this, &ThisClass::Slide);
	EAWInputComponent->BindActionByTag(GEAWSettings.GetInputConfigAsset(), GEAWGameplayTags.INPUT_SPIN_TAG, ETriggerEvent::Triggered, this, &ThisClass::Spin);
	EAWInputComponent->BindActionByTag(GEAWSettings.GetInputConfigAsset(), GEAWGameplayTags.INPUT_RESTORE_POSITION_TAG, ETriggerEvent::Triggered, this, &ThisClass::RestorePosition);
	EAWInputComponent->BindActionByTag(GEAWSettings.GetInputConfigAsset(), GEAWGameplayTags.INPUT_PRIMARY_ACTION_TAG, ETriggerEvent::Triggered, this, &ThisClass::EnhancedStartPrimaryAction);
}

void AEAWPlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerPawn = Cast<AEAWPlayerPawnBase>(InPawn);
}

void AEAWPlayerControllerBase::EnhancedMove(const FInputActionValue& Value)
{
	if (IsValid(PlayerPawn))
	{
		PlayerPawn->MoveRight(Value[0]);
		PlayerPawn->MoveForward(Value[1]);
		PlayerPawn->MoveUp(Value[2]);
	}
}

void AEAWPlayerControllerBase::EnhancedRotate(const FInputActionValue& Value)
{
	if (IsValid(PlayerPawn))
	{
		PlayerPawn->RotateYaw(Value[0]);
		PlayerPawn->RotatePitch(Value[1]);
	}
}

void AEAWPlayerControllerBase::EnhancedZoom(const FInputActionValue& Value)
{
	if (IsValid(PlayerPawn))
	{
		PlayerPawn->Zoom(Value[0]);
		// Uncomment lines below to use Zooming to cursor functionality
		// bool DidHit;
		// ECollisionChannel CollisionChannel = ECollisionChannel::ECC_WorldStatic;
		// FVector ImpactPointUnderCursor = GetImpactPointUnderCursor(CollisionChannel, false, DidHit);
		// PlayerPawn->ZoomToCursor(Value[0], CollisionChannel, ImpactPointUnderCursor, DidHit);
	}
}

void AEAWPlayerControllerBase::Slide()
{
	if (IsValid(PlayerPawn))
	{
		float MouseXDelta, MouseYDelta;
		GetInputMouseDelta(MouseXDelta, MouseYDelta);
		PlayerPawn->MoveRight(MouseXDelta * -1.0f);
		PlayerPawn->MoveForward(MouseYDelta * -1.0f);
	}
}

void AEAWPlayerControllerBase::Spin()
{
	if (IsValid(PlayerPawn))
	{
		float MouseXDelta, MouseYDelta;
		GetInputMouseDelta(MouseXDelta, MouseYDelta);
		PlayerPawn->RotateYaw(MouseXDelta * -1.0f);
		PlayerPawn->RotatePitch(MouseYDelta * -1.0f);
	}
}

void AEAWPlayerControllerBase::RestorePosition()
{
	if (IsValid(PlayerPawn))
	{
		PlayerPawn->LoadPositionSaveFormat(PlayerPawn->GetLastSavedPosition());
	}
}

void AEAWPlayerControllerBase::EnhancedStartPrimaryAction()
{
	DeselectAllActors();
	TrySelectActor();
}

FVector AEAWPlayerControllerBase::GetMousePositionInWorldSpace()
{
	FVector WorldLocation, WorldDirection;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	return WorldLocation - WorldDirection * (WorldLocation.Z / WorldDirection.Z);
}

FVector AEAWPlayerControllerBase::GetImpactPointUnderCursor(ECollisionChannel TraceChannel, bool TraceComplex, bool& DidHit)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(TraceChannel, TraceComplex, HitResult);
	DidHit = HitResult.IsValidBlockingHit();
	return DidHit ? HitResult.ImpactPoint : FVector::ZeroVector;
}

AActor* AEAWPlayerControllerBase::GetActorUnderCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	return HitResult.GetActor();
}

bool AEAWPlayerControllerBase::TrySelectActor()
{
	AActor* SelectedActor = GetActorUnderCursor();
	if (IsValid(SelectedActor) && SelectedActor->Implements<USelectable>())
	{
		DeselectAllActors();
		ISelectable::Execute_SelectObject(SelectedActor);
		AddSelectedActorToList(SelectedActor);
		return true;
	}
	return false;
}

void AEAWPlayerControllerBase::AddSelectedActorToList(AActor* SelectedActor)
{
	SelectedActors.Add(SelectedActor);
}

void AEAWPlayerControllerBase::DeselectAllActors()
{
	for (AActor* SelectedActor : SelectedActors)
	{
		// Actors that not implementing USelectable interface can't be stored in SelectedActors
		ISelectable::Execute_DeselectObject(SelectedActor);
	}
	SelectedActors.Empty();
}