// NiVeron Games 2023. All rights reserved.

#include "Gameplay/TradeRoute.h"
#include "Gameplay/StarSystem.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "EmpireAtWarUE5/EmpireAtWarUE5.h"

// Sets default values
ATradeRoute::ATradeRoute()
	: StartStarSystem(nullptr)
	, EndStarSystem(nullptr)
	, bAllowShipsMovement(false)
	, TradeShipsCount(0)
	, TradeShipClass(nullptr)
	, TotalPathTime(10.0f)
	, SectionMesh(nullptr)
	, SectionMeshScale(1.0f)
	, SectionMaterial(nullptr)
	, ForwardAxis(ESplineMeshAxis::Z)
	, CollisionType(ECollisionEnabled::NoCollision)
	, TradeShips()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	RouteSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RouteSpline"));
	RouteSpline->SetupAttachment(Root);
	RouteSpline->bDrawDebug = true;
	RouteSpline->Duration = TotalPathTime;

	PrimaryActorTick.bCanEverTick = true;
}

void ATradeRoute::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const int32 MaxSectionIndex = RouteSpline->GetNumberOfSplinePoints() - 1;

	if (StartStarSystem.Get())
	{
		RouteSpline->SetLocationAtSplinePoint(0, StartStarSystem->GetActorLocation(), ESplineCoordinateSpace::World);
	}

	if (EndStarSystem.Get())
	{
		RouteSpline->SetLocationAtSplinePoint(MaxSectionIndex, EndStarSystem->GetActorLocation(), ESplineCoordinateSpace::World);
	}

	if (!SectionMesh) return;

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	for (int32 SplineCount = 0; SplineCount < MaxSectionIndex; SplineCount++)
	{
		USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

		Streamable.RequestAsyncLoad(SectionMesh.ToSoftObjectPath(), [this, SplineMeshComponent] {
			SplineMeshComponent->SetStaticMesh(SectionMesh.Get());
		});

		Streamable.RequestAsyncLoad(SectionMaterial.ToSoftObjectPath(), [this, SplineMeshComponent] {
			SplineMeshComponent->SetMaterial(0, SectionMaterial.Get());
		});

		SplineMeshComponent->SetMobility(EComponentMobility::Movable);
		SplineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		SplineMeshComponent->RegisterComponentWithWorld(GetWorld());
		SplineMeshComponent->AttachToComponent(RouteSpline, FAttachmentTransformRules::KeepRelativeTransform);

		FVector StartPoint, StartTangent, EndPoint, EndTangent;
		RouteSpline->GetLocationAndTangentAtSplinePoint(SplineCount, StartPoint, StartTangent, ESplineCoordinateSpace::Local);
		RouteSpline->GetLocationAndTangentAtSplinePoint(SplineCount + 1, EndPoint, EndTangent, ESplineCoordinateSpace::Local);

		SplineMeshComponent->SetStartAndEnd(StartPoint, StartTangent, EndPoint, EndTangent, true);
		SplineMeshComponent->SetStartScale(FVector2D(SectionMeshScale));
		SplineMeshComponent->SetEndScale(FVector2D(SectionMeshScale));
		SplineMeshComponent->SetCollisionEnabled(CollisionType);
		SplineMeshComponent->SetForwardAxis(ForwardAxis);
	}
}

void ATradeRoute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateTradeShipsLocation(DeltaTime);
}

void ATradeRoute::BeginTrade()
{
	if (!TradeShipClass.LoadSynchronous() || !GetWorld()) return;

	for (int32 i = 0; i < TradeShipsCount; ++i)
	{
		const float SpawnPoint = FMath::FRandRange(0.0f, 1.0f);
		const FTransform SpawnTransform = RouteSpline->GetTransformAtDistanceAlongSpline(SpawnPoint, ESplineCoordinateSpace::World);

		AActor* TradeShip = GetWorld()->SpawnActor<AActor>(TradeShipClass.Get(), SpawnTransform);
		if (TradeShip)
		{
			TradeShips.Emplace(TradeShip, FTradeShipMovementData(FMath::RandBool(), SpawnPoint));
		}
	}
}

TPair<FGameplayTag, FGameplayTag> ATradeRoute::GetOwningStarSystemTags() const
{
	ensure(StartStarSystem.Get() && EndStarSystem.Get());
	return TPairInitializer(StartStarSystem.Get()->GetStarSystemTag(), EndStarSystem.Get()->GetStarSystemTag());
}

void ATradeRoute::UpdateTradeShipsLocation(float DeltaTime)
{
	if (TradeShips.IsEmpty() || !bAllowShipsMovement)
	{
		return;
	}

	for (auto& [TradeShip, MovementData] : TradeShips)
	{
		const float DirectionModifier = MovementData.bReverseMovement ? -1.0f : 1.0f;
		MovementData.Position = MovementData.Position + DirectionModifier / TotalPathTime * DeltaTime;

		const float Distance = MovementData.Position * RouteSpline->GetSplineLength();

		const FVector Position = RouteSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		const FVector Direction = RouteSpline->GetDirectionAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		// Avoid ship moves backwards in reverse movement
		const FRotator RotationModifier = MovementData.bReverseMovement ? FRotator(0.0f, -180.0f, 0.0f) : FRotator(0.0f);
		const FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator() + RotationModifier;

		TradeShip->SetActorLocationAndRotation(Position, Rotation);

		if (MovementData.Position >= 1.0f || MovementData.Position <= 0.0f)
		{
			MovementData.bReverseMovement = !MovementData.bReverseMovement;
		}
	}
}
