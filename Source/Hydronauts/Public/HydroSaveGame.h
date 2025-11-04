// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HydroSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class HYDRONAUTS_API UHydroSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UHydroSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 SlotIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector WorldLocation;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FRotator WorldRotation;
};

// The Above Was Coded By Devin Brown P2798179