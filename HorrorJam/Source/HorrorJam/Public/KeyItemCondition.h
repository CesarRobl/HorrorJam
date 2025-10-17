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

	 bool EvaluateCondition_Implementation(const UObject* Context, int Index) const override
	{
	

		 if(!Context)
			 return false;

		

		 UWorld* World = Context->GetWorld();
		 if (!World)
			 return false;

		 AHorrorJamCharacter* Player = Cast<AHorrorJamCharacter>(World->GetFirstPlayerController()->GetPawn());

		 if (!Player)
			 return false;

		 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Player is carrying: %s"), Player->CarriedItem ? *Player->CarriedItem->ItemName : TEXT("Nothing")));

		 return Player->CarriedItem->ItemName == RequiredItem;
	};
	
};
