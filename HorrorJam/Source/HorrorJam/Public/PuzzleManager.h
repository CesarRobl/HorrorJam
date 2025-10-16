// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleRule.h"
#include "PuzzleSignal.h"
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
	FName PuzzleID;



	UFUNCTION(BlueprintCallable)
	void CheckPuzzleCompletion()
	{
		if (!PuzzleRule)
			return;

		bool bTest = PuzzleRule->Conditions[0]->EvaluateCondition_Implementation(PuzzleSignals[0]);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Condition evaluated to: %s"), bTest ? TEXT("True") : TEXT("False")));
	}



};
