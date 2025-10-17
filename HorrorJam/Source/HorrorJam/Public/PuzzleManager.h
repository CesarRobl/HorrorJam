// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleRule.h"
#include "PuzzleSignal.h"
#include "EventActor.h"
#include "PuzzleManager.generated.h"

UCLASS()
class HORRORJAM_API APuzzleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPuzzleRule* PuzzleRule;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<APuzzleSignal*> PuzzleSignals;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<bool> PuzzleStates;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AEventActor*> PuzzleEvents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName PuzzleID;



	UFUNCTION(BlueprintCallable)
	void CheckPuzzleCompletion(int SignalIndex)
	{
		if (!PuzzleRule)
			return;

		bool bTest = PuzzleRule->Conditions[SignalIndex]->EvaluateCondition_Implementation(PuzzleSignals[SignalIndex], SignalIndex);
		UpdatePuzzleState(SignalIndex, bTest);


		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Condition evaluated to: %s"), bTest ? TEXT("True") : TEXT("False")));
	}

	void UpdatePuzzleState(int SignalIndex, bool NewState)
	{
		PuzzleStates[SignalIndex] = NewState;

		int TrueCount = 0;

		for (bool State : PuzzleStates)
		{
			if (State)
				TrueCount++;
		}

		if (TrueCount == PuzzleStates.Num())
		{
			// Puzzle completed
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Puzzle %s Completed!"), *PuzzleID.ToString()));
			

			if(PuzzleEvents.Num() > 0)
				for (auto& Event : PuzzleEvents)
				{
					if (Event)
						Event->TriggerEvent();
				}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Puzzle %s Progress: %d/%d"), *PuzzleID.ToString(), TrueCount, PuzzleStates.Num()));
		}
	}
	



};
