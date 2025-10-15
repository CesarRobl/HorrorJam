// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include  "Public/Item.h"
#include "Public/Basket.h"
#include "HorrorJamCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AHorrorJamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MovementAngle = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AItem*> ItemsInRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 ItemIndex = 0;

	

public:

	/** Constructor */
	AHorrorJamCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsNearBasket = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ABasket* PlayerBasket = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AItem* CarriedItem = nullptr;




protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	
	UFUNCTION(BlueprintCallable)
	void PickUpItem()
	{
		if (ItemsInRange.Num() <= 0)
			return;

		AItem* Item = GetClosestItem();

		
		AttachItem(Item);
	}

	UFUNCTION(BlueprintCallable)
	void AttachItem(AItem* Item)
	{
		if (GetMesh()->DoesSocketExist(FName("ItemSocket"))) {
			CarriedItem = Item;

			Item->TurnOffCollision();
			Item->AttachToComponent(GetMesh(),
				FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("ItemSocket"));
		}
	}

	UFUNCTION(BlueprintCallable)	
	void DropItem()
	{
		CarriedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		// If player is near basket and is carrying an item, add item to basket
		if (bIsNearBasket)
		{
			PlayerBasket->AddItem(CarriedItem);

			CarriedItem = nullptr;
			return;
		}

		
		CarriedItem->ItemMesh->SetSimulatePhysics(true);
		CarriedItem->SetActorEnableCollision(true);
		CarriedItem = nullptr;
	}

	UFUNCTION(BlueprintCallable)
	AItem* GetClosestItem() const
	{
		if (ItemsInRange.Num() <= 0)
			return nullptr;
			
		FVector PlayerLocation = GetActorLocation();
		float ClosestDist = TNumericLimits<float>::Max();
		AItem* ClosestItem = nullptr;

		for (AItem* Item : ItemsInRange)
		{
			float Dist = FVector::Dist(PlayerLocation, Item->GetActorLocation());
			if (Dist < ClosestDist)
			{
				ClosestDist = Dist;
				ClosestItem = Item;
			}
		}

		return ClosestItem;
	}
	
	UFUNCTION(BlueprintCallable)
	bool ItemIsNear() const
	{
		return ItemsInRange.Num() > 0;
	}

	UFUNCTION(BlueprintCallable)
	bool IsCarryingItem() const
	{
		return CarriedItem != nullptr;
	}



public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

