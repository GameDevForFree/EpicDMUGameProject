// All code by Michael Threlfall P2797637


#include "SharkAIController2.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void ASharkAIController2::BeginPlay()
{
	Super::BeginPlay();
	// Gets the players character
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 1);
}

void ASharkAIController2::Tick(float DeltaSeconds)
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
