// All code here is by Alex Robertson P2607829

#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h" 

ACheckpoint::ACheckpoint()
{
    PrimaryActorTick.bCanEverTick = false; // disables the checkpoint needing to update every frame

    // creates a mesh component and sets it as the root component of the actor

    CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
    RootComponent = CheckpointMesh;

    // creates a box component that will detect overlaps

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 100.f)); // creates a sizable invisible triggerbox cube that detects overlaps (to activate it as the current primary checkpoint)
    TriggerBox->SetCollisionProfileName(TEXT("Trigger")); // sets the box to detect overlaps but not to block objects itself

    bIsActive = false; // sets the checkpoint to be inactive until a player has overlapped with it and activated it
}

void ACheckpoint::BeginPlay()
{
    Super::BeginPlay();
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin); // links the overlap event onto TriggerBox
}

// when something overlaps the triggerbox, this function is called automatically. It also has info on what overlapped it

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{

    AMainCharacter* Player = Cast<AMainCharacter>(OtherActor); // attempts to cast the actor that overlapped into the AMainCharacter class & if that actor isn't the player, then player is null.
    if (Player) // if that overlapped actor is the player, it enables this checkpoint to be the main active one and 
    {
        bIsActive = true;
        Player->SetCheckpointLocation(GetActorLocation()); // this calls a function inside the player MainCharacter class using this checkpoint's location and sets it as the player's respawn point.

    }
}
