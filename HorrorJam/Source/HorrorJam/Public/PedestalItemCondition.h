// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UPuzzleConditionNode.h"
#include "PuzzleManager.h"
#include "EngineUtils.h"
#include "PedestalItemCondition.generated.h"


UCLASS()
class HORRORJAM_API UPedestalItemCondition : public UUPuzzleConditionNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString RequiredItem;

	bool EvaluateCondition_Implementation(const UObject* Context, int Index) const override
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

		APuzzleSignal* PuzzleSignal = PuzzleManager->PuzzleSignals[Index];

		if(!PuzzleSignal || !PuzzleSignal->PedestalItem)
			return false;

		AItem* PedestalItem = PuzzleSignal->PedestalItem;

		if(!PedestalItem)
			return false;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Pedestal has: %s"), PedestalItem ? *PedestalItem->ItemName : TEXT("Nothing")));

		return PedestalItem->ItemName == RequiredItem;
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

			if (It->PuzzleID == ManagerID)
			{
				
				return *It;
			}
			
		}

		return nullptr;
	}
};
