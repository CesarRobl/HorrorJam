

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UPuzzleConditionNode.h"
#include "PuzzleRule.generated.h"


UENUM(BlueprintType)
enum class EPuzzleTriggerMode : uint8
{
	Reactive,
	OneShot,
	Latched
};

UCLASS(BlueprintType)
class HORRORJAM_API UPuzzleRule : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName RuleID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPuzzleTriggerMode TriggerMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UUPuzzleConditionNode*> Conditions;
	
};
