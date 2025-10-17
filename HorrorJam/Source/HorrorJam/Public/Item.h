// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Item.generated.h"

UCLASS()
class HORRORJAM_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPhysicsConstraintComponent* ItemConstraint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsKeyItem = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLargeItem = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsBasket = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 ItemWeight = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TurnOffCollision()
	{
		ItemMesh->SetSimulatePhysics(false);
		SetActorEnableCollision(false);
	}

	void MoveItem(float Speed, FVector PlayerForward)
	{
		FVector MovementDirection = PlayerForward * Speed;
		FVector TargetLocation = ItemMesh->GetRelativeLocation() + MovementDirection;

		FVector NewLocation = FMath::VInterpTo(ItemMesh->GetRelativeLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), 4);

		ItemMesh->SetRelativeLocation(NewLocation);
	}


};
