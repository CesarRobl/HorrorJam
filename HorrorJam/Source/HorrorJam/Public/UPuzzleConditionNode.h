// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UPuzzleConditionNode.generated.h"

/**
 * 
 */
UCLASS()
class HORRORJAM_API UUPuzzleConditionNode : public UDataAsset
{
	GENERATED_BODY()
	
	public:

		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Puzzle Condition")
		bool EvaluateCondition(const UObject* Context) const;
		virtual bool EvaluateCondition_Implementation(const UObject* Context) const {return false; }
};
