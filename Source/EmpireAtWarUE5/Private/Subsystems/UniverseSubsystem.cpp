// NiVeron Games 2022. All rights reserved.

#include "Subsystems/UniverseSubsystem.h"
#include "Data/UniverseDataTable.h"
#include "Gameplay/StarSystem.h"

UUniverseSubsystem::UUniverseSubsystem()
	: bShouldBeCreated(false)
	, UniverseData()
	, StarSystemClass()
	, UniverseMap()
{
}

void UUniverseSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	CreateUniverse();
}

void UUniverseSubsystem::CreateUniverse()
{
	checkf(IsValid(UniverseData), TEXT("UUniverseSubsystem::CreateUniverse(): UniverseData is invalid."));
	for (FName& RowName : UniverseData->GetRowNames())
	{
		if (FStarSystemData* Data = UniverseData->FindRow<FStarSystemData>(RowName, FString()))
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FTransform StarSystemTransform = FTransform(Data->Position); // C2664
			AStarSystem* CelestialBody = Cast<AStarSystem>(GetWorld()->SpawnActor(StarSystemClass, &StarSystemTransform, SpawnInfo));
			CelestialBody->SetStarSystemData(Data);
			UniverseMap.Add(RowName, CelestialBody);
		}
	}
}