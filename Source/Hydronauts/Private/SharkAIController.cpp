// This is all code by Michael Threlfall P2797637

#include "SharkAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"

ASharkAIController::ASharkAIController()
{
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/tralalerotralala.tralalerotralala"));
    if (SoundAsset.Succeeded())
    {
        SharkSFX = SoundAsset.Object;
    }
}

void ASharkAIController::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ASharkAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn || !PlayerPawn)
        return;

    if (LineOfSightTo(PlayerPawn))
    {
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn, 5.0f);

       
        if (!bHasPlayedSound && SharkSFX)
        {
            UGameplayStatics::PlaySoundAtLocation(this, SharkSFX, ControlledPawn->GetActorLocation());
            bHasPlayedSound = true; // mark as played
        }
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}
