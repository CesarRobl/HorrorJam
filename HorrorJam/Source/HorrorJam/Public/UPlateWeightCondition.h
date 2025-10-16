// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UPuzzleConditionNode.h"
#include "PuzzleManager.h"
#include "EngineUtils.h"
#include "UPlateWeightCondition.generated.h"

/**
 * 
 */
UCLASS()
class HORRORJAM_API UUPlateWeightCondition : public UUPuzzleConditionNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RequiredWeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PlateIndex = 0;

	bool EvaluateCondition_Implementation(const UObject* Context) const override
	{
		if (!Context)
			return false;

		UWorld* World = Context->GetWorld();
		if (!World)
			return false;

		APuzzleManager* PuzzleManager = nullptr;

		PuzzleManager = GetPuzzleManager(Context);
		
		if(!PuzzleManager)
			return false;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
			FString::Printf(TEXT("Hello")));

		return PuzzleManager->PuzzleSignals[0]->Weight >= RequiredWeight;
	}

	APuzzleManager* GetPuzzleManager(const UObject* Context) const
	{
		if (!Context)
			return nullptr;
		UWorld* World = Context->GetWorld();
		if (!World)
			return nullptr;
		for (TActorIterator<APuzzleManager> It(World); It; ++It)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
				FString::Printf(TEXT("Found Puzzle Manager: %s"), *It->PuzzleID.ToString()));

			if(It->PuzzleID == ManagerID)
				return *It;
		}
		return nullptr;
	}

};
