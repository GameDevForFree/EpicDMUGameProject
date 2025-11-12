// All code here is by Alex Robertson P2607829

#include "DeathBarrier.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Checkpoint.h"
#include "MainCharacter.h"
#include "ScoreManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

ADeathBarrier::ADeathBarrier()
{
    PrimaryActorTick.bCanEverTick = false; // disables the death barrier needing to update every frame

    // creates a box component that will detect overlaps

    KillZone = CreateDefaultSubobject<UBoxComponent>(TEXT("KillZone"));
    RootComponent = KillZone;

    KillZone->InitBoxExtent(FVector(200.f, 200.f, 100.f)); // sets the size of the killzone box
    KillZone->SetCollisionProfileName(TEXT("Trigger")); // sets the box to detect overlaps but not to block objects itself
    KillZone->SetGenerateOverlapEvents(true); // enables overlap event generation


    // creates a mesh component and sets it as the root component of the actor
    BarrierMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierMesh"));
    BarrierMesh->SetupAttachment(RootComponent);

    // makes the mesh non-collidable so only the killzone can trigger overlap events
    BarrierMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // sets object default scale
    BarrierMesh->SetRelativeScale3D(FVector(1.f));


    // links the overlap event onto KillZone
    KillZone->OnComponentBeginOverlap.AddDynamic(this, &ADeathBarrier::OnOverlapBegin);
}

void ADeathBarrier::BeginPlay()
{
    Super::BeginPlay();
}

// when something overlaps the KillZone, this function is called automatically. It also has info on what overlapped it

void ADeathBarrier::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    AMainCharacter* Player = Cast<AMainCharacter>(OtherActor); // checks if the other actor overlapping is the main character
    if (Player)
    {
        
        Player->RespawnAtCheckpoint(); // if the other overlapping actor was the main character, then call the main character respawn function and respawn the player

       

        // finds the scoremanager actor in the level and substracts 15 points from the score hud each time the player dies
        AScoreManager* ScoreManager = Cast<AScoreManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AScoreManager::StaticClass()));
        if (ScoreManager)
        {
            ScoreManager->SubtractScore(15); 
        }
    }
}
