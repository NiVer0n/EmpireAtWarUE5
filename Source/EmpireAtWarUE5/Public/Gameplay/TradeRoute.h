// NiVeron Games 2023. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameplayTagContainer.h"
#include "TradeRoute.generated.h"

class USplineComponent;
class UMaterialInterface;
class AStarSystem;

USTRUCT()
struct FTradeShipMovementData
{
	GENERATED_BODY()

	FTradeShipMovementData() = default;

	FTradeShipMovementData(bool InReverseMovement, float InPosition)
		: bReverseMovement(InReverseMovement)
		, Position(InPosition)
	{
	}

	UPROPERTY()
	bool bReverseMovement;

	UPROPERTY()
	float Position;
};

UCLASS()
class EMPIREATWARUE5_API ATradeRoute : public AActor
{
	GENERATED_BODY()

public:
	ATradeRoute();

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginTrade();

	FORCEINLINE TPair<FGameplayTag, FGameplayTag> GetOwningStarSystemTags() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USplineComponent> RouteSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Settings")
	TSoftObjectPtr<AStarSystem> StartStarSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Settings")
	TSoftObjectPtr<AStarSystem> EndStarSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Ships")
	bool bAllowShipsMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Ships", meta = (EditCondition = "bAllowShipsMovement"))
	int32 TradeShipsCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Ships", meta = (EditCondition = "bAllowShipsMovement"))
	TSoftClassPtr<AActor> TradeShipClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Ships", meta = (EditCondition = "bAllowShipsMovement"))
	float TotalPathTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Spline")
	TSoftObjectPtr<UStaticMesh> SectionMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Spline")
	float SectionMeshScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Spline")
	TSoftObjectPtr<UMaterialInterface> SectionMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Spline")
	TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TradeRoute|Spline")
	TEnumAsByte<ECollisionEnabled::Type> CollisionType;

private:
	void UpdateTradeShipsLocation(float DeltaTime);

	TMap<AActor*, FTradeShipMovementData> TradeShips;
};
