// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/** List of locally participating players in this game instance */
UPROPERTY()
TArray<TObjectPtr<ULocalPlayer>> LocalPlayers;

/**
 * 
 */
UCLASS()
class HYDRONAUTS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
};
