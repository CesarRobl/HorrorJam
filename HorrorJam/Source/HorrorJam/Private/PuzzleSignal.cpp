// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleSignal.h"

// Sets default values
APuzzleSignal::APuzzleSignal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleSignal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleSignal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

