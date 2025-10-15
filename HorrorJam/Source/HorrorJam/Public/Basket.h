// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Basket.generated.h"

/**
 * 
 */
UCLASS()
class HORRORJAM_API ABasket : public AItem
{
	GENERATED_BODY()

	public:
		
		TArray<AItem*> Inventory;

		UFUNCTION(BlueprintCallable)
		void AddItem(AItem* Item)
		{
			if(IsFull())
				return;

			Item->SetActorHiddenInGame(true);
			Inventory.Add(Item);
		}

		UFUNCTION(BlueprintCallable)
		void RemoveItem()
		{
			if(!ItemToTake)
				return;

			ItemToTake->SetActorHiddenInGame(false);
			AttachToPlayer();

			Inventory.Remove(ItemToTake);
			ItemToTake = nullptr;
		}
		
		UFUNCTION(BlueprintNativeEvent)
		void AttachToPlayer();
		void AttachToPlayer_Implementation()
		{
		}

		UFUNCTION(BlueprintCallable)
		void SelectNextItem(int InvIncrement, AItem*& SelectedItem)
		{
			if(Inventory.Num() <= 0)
				return;
			
			InventoryIndex += InvIncrement;
			
			if(InventoryIndex >= Inventory.Num() - 1)
				InventoryIndex = 0;

			if (InventoryIndex < 0)
				InventoryIndex = Inventory.Num() - 1;

			SelectedItem = Inventory[InventoryIndex];
			ItemToTake = SelectedItem;

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Selected Item: %s"), *SelectedItem->GetName()));
		}


	protected:
		
		int32 InventoryIndex = 0;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		AItem* ItemToTake = nullptr;

		void BeginPlay() override
		{
			Super::BeginPlay();
			

		}


		UFUNCTION(BlueprintCallable)
		bool IsFull() const
		{
			return Inventory.Num() >= 4;
		}

		
};
