// Fill out your copyright notice in the Description page of Project Settings.


#include "SharkAIController.h"
#include "Kismet/GameplayStatics.h"

void ASharkAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	SetFocus(PlayerPawn);
}

// Added by Michael Threlfall P2797637
void ASharkAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MoveToActor(PlayerPawn, 10);
}

void ASharkAIController::LineOfSightTo(AActor* targetActor)
{
}
