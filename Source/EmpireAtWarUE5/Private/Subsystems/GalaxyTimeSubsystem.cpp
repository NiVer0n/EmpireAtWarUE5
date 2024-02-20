// NiVeron Games 2022. All rights reserved.

#include "Subsystems/GalaxyTimeSubsystem.h"
#include "Engine/EAWSettings.h"

UGalaxyTimeSubsystem::UGalaxyTimeSubsystem()
	: CurrentTime(0.0f)
	, CurrentDay(0)
	, TimeUpdateRate(1.0f)
	, NextUpdateTime(TimeUpdateRate)
{
}

void UGalaxyTimeSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	OnGalaxyDayChanged.Broadcast(++CurrentDay);
}

void UGalaxyTimeSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateGameTime(DeltaTime);
}

void UGalaxyTimeSubsystem::UpdateGameTime(float DeltaTime)
{
	CurrentTime += DeltaTime;

	if (CurrentTime < NextUpdateTime)
	{
		return;
	}
	// The implementation is similar to a timer, but the timer does not respond to Time dilation changes.
	const int32 UpdateCallCount = FMath::TruncToInt(CurrentTime - NextUpdateTime / TimeUpdateRate) + 1;
	for (int32 CallIdx = 0; CallIdx < UpdateCallCount; ++CallIdx)
	{
		const float DayDuration = GEAWSettings.GetGalaxyDayDuration();
		OnGalaxyTimeChanged.Broadcast(CurrentTime, DayDuration);

		if (FMath::Floor(FMath::Fmod(CurrentTime, DayDuration)) == 0.0f)
		{
			OnGalaxyDayChanged.Broadcast(++CurrentDay);
		}
	}

	NextUpdateTime += UpdateCallCount * TimeUpdateRate;
}
