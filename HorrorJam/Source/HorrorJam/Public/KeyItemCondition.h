// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UPuzzleConditionNode.h"
#include "Item.h"
#include "HorrorJamCharacter.h"
#include "KeyItemCondition.generated.h"

/**
 * 
 */
UCLASS()
class HORRORJAM_API UKeyItemCondition : public UUPuzzleConditionNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString RequiredItem;

	 bool EvaluateCondition_Implementation(const UObject* Context) const override
	{
	

		 if(!Context)
			 return false;

		

		 UWorld* World = Context->GetWorld();
		 if (!World)
			 return false;

		 AHorrorJamCharacter* Player = Cast<AHorrorJamCharacter>(World->GetFirstPlayerController()->GetPawn());

		 if (!Player)
			 return false;

		 return Player->CarriedItem->ItemName == RequiredItem;
	};
	
};
