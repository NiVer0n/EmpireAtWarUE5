// NiVeron Games 2022. All rights reserved.

#include "Subsystems/GalaxyTimeSubsystem.h"
#include "Engine/EAWSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogGalaxyTime, All, All);

UGalaxyTimeSubsystem::UGalaxyTimeSubsystem()
	: CurrentTime(0.0f)
	, CurrentDay(0)
	, TimeUpdateRate(1.0f)
	, NextUpdateTime(TimeUpdateRate)
{
}

void UGalaxyTimeSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	UE_LOG(LogGalaxyTime, Display, TEXT("%s"), ANSI_TO_TCHAR("__FUNCTION__"));

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

		UE_LOG(LogGalaxyTime, Display, TEXT("Galaxy Time changed. New time: %f"), CurrentTime);

		if (FMath::Floor(FMath::Fmod(CurrentTime, DayDuration)) == 0.0f)
		{
			OnGalaxyDayChanged.Broadcast(++CurrentDay);
			UE_LOG(LogGalaxyTime, Display, TEXT("Galaxy Day changed. New day: %i"), CurrentDay);
		}
	}

	NextUpdateTime += UpdateCallCount * TimeUpdateRate;
}
