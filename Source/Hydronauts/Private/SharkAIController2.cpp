// All code by Michael Threlfall P2797637


#include "SharkAIController2.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void ASharkAIController2::BeginPlay()
{
    Super::BeginPlay();
    // Gets the players character
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 1);

    // gets the audio file and assigns it to the SoundAsset object variable
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/tralalerotralala.tralalerotralala"));
    if (SoundAsset.Succeeded())
    {
        SharkSFX = SoundAsset.Object;
    }
}

void ASharkAIController2::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Shark will only focus on and move towards the player if it has a direct line of sight
    if (PlayerPawn)
    {
        if (LineOfSightTo(PlayerPawn))
        {
            SetFocus(PlayerPawn);
            MoveToActor(PlayerPawn, 5.0f);

            // plays the audio at the players locations and makes sure it only plays once 
            if (!bHasPlayedSound && SharkSFX)
            {
                UGameplayStatics::PlaySoundAtLocation(this, SharkSFX, PlayerPawn->GetActorLocation());
                bHasPlayedSound = true;
            }
        }
        else
        {
            // If the shark loses sight of the player then it will stop following them and lose focus
            ClearFocus(EAIFocusPriority::Gameplay);
            StopMovement();
        }
    }
}