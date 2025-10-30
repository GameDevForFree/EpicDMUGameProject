// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "PlayButton.generated.h"

/**
 * 
 */
UCLASS()
class HYDRONAUTS_API UPlayButton : public UButton
{
	GENERATED_BODY()

private:
	FLinearColor UColorGrey;
	
public:
	UPlayButton();

	
};
