// NiVeron Games 2022. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GalaxyTimeSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGalaxyTimeChangedDelegate, float, CurrentTime, float, DayDuration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGalaxyDayChangedDelegate, int32, CurrentDay);

/**
 * Class for game time control.
 */
UCLASS()
class EMPIREATWARUE5_API UGalaxyTimeSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	/** Calls when game time counter is updated (once per second). */
	UPROPERTY(BlueprintAssignable, Category = "GameTime")
	FOnGalaxyTimeChangedDelegate OnGalaxyTimeChanged;

	/** Calls when game day counter is updated (the frequency is specified in UEAWSettings::GetGalaxyDayDuration). */
	UPROPERTY(BlueprintAssignable, Category = "GameTime")
	FOnGalaxyDayChangedDelegate OnGalaxyDayChanged;

protected:
	UGalaxyTimeSubsystem();

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { return TStatId(); }
	
	/* Time since the start of the game. */
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly, Category = "GameTime")
	float CurrentTime;
	
	/* Current game day. Every time it changes, player receives new taxes from controlled planets. */
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly, Category = "GameTime")
	int32 CurrentDay;

private:
	void UpdateGameTime(float CurrentTime);

	/* How often should the game time counter be updated. 1 second by default. */
	UPROPERTY()
	float TimeUpdateRate;

	/* How much time should pass before the next game time update. Affected by Time Dilation. */
	UPROPERTY()
	float NextUpdateTime;
};
