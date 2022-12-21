// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player/EAWPlayerPawnBase.h"
#include "EAWPlayerControllerBase.generated.h"

struct FInputActionValue;
class UInputAction;
class UDA_InputConfig;
class UInputMappingContext;
class UFactionComponent;

/**
 * 
 */
UCLASS()
class EMPIREATWARUE5_API AEAWPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	/* Sets player data on first game start or from save. */
	void ApplyStartupData(/* @TODO: place startup data struct here. */);

	/** Return mouse 2D position vector converted to 3d vector */
	FVector GetMousePositionInWorldSpace();
	FVector GetImpactPointUnderCursor(ECollisionChannel TraceChannel, bool TraceComplex, bool& DidHit);
	AActor* GetActorUnderCursor();
	FORCEINLINE FVector2D GetSelectionStartPoint() const { return SelectionStartPoint; };
	FORCEINLINE UFactionComponent* GetFactionComponent() const { return FactionComponent; }

protected:
	AEAWPlayerControllerBase();

	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void EnhancedMove(const FInputActionValue& Value);
	virtual void EnhancedRotate(const FInputActionValue& Value);
	virtual void EnhancedZoom(const FInputActionValue& Value);
	virtual void Slide();
	virtual void Spin();
	virtual void RestorePosition();
	virtual void EnhancedStartPrimaryAction();

	bool TrySelectActor();

	UPROPERTY(Transient)
	AEAWPlayerPawnBase* PlayerPawn;

	UPROPERTY()
	TArray<AActor*> SelectedActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFactionComponent* FactionComponent;

private:
	void AddSelectedActorToList(AActor* SelectedActor);
	void DeselectAllActors();

	UPROPERTY()
	FVector2D SelectionStartPoint;
};
