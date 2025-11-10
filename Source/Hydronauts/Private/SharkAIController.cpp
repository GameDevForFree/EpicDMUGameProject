// This is all code by Michael Threlfall P2797637


#include "SharkAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void ASharkAIController::BeginPlay()
{
	Super::BeginPlay();
	// Gets the players character
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ASharkAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// Shark loses focus of Player if something is obstructing its view
	if (PlayerPawn)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			SetFocus(PlayerPawn);
			MoveToActor(PlayerPawn, 5.0f);
		}
		else
		{
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}
	}
}