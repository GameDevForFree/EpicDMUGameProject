// Fill out your copyright notice in the Description page of Project Settings.


#include "SharkAIController.h"
#include "Kismet/GameplayStatics.h"

void ASharkAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	SetFocus(PlayerPawn);
}