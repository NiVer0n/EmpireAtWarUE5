// NiVeron Games 2022. All rights reserved.

#include "Utils/SubsystemUtils.h"
#include "Subsystems/FactionsSubsystem.h"

template <class T>
T* USubsystemUtils::GetWorldSubsystem(UWorld* World)
{
	checkf(IsValid(World), TEXT("USubsystemUtils::GetWorldSubsystem() Can not get %s subsystem, because World is not valid!"), *GetNameSafe(T::StaticClass()));

	UWorldSubsystem* WorldSubsystem = World->GetSubsystemBase(T::StaticClass());
	checkf(IsValid(WorldSubsystem), TEXT("USubsystemUtils::GetWorldSubsystem() Can not get %s subsystem, because there is no such!"), *GetNameSafe(T::StaticClass()));

	return StaticCast<T*>(WorldSubsystem);
}

UFactionsSubsystem* USubsystemUtils::GetFactionsSubsystem(UWorld* World)
{
	return GetWorldSubsystem<UFactionsSubsystem>(World);
}