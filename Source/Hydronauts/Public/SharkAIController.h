// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SharkAIController.generated.h"

/**
 * 
 */
UCLASS()
class HYDRONAUTS_API ASharkAIController : public AAIController
{
	GENERATED_BODY()

	protected:
	virtual void BeginPlay() override;
};

