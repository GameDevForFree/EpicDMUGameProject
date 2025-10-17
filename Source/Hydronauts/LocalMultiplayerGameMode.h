// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LocalMultiplayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HYDRONAUTS_API ALocalMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()
	protected:
		virtual void BeginPlay();
};
