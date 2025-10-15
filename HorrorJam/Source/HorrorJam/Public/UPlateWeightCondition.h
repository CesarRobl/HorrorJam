// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UPuzzleConditionNode.h"
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

};
