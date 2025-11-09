#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h" // Replace with your character class header

ACheckpoint::ACheckpoint()
{
    PrimaryActorTick.bCanEverTick = false;

    CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckpointMesh"));
    RootComponent = CheckpointMesh;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

    bIsActive = false;
}

void ACheckpoint::BeginPlay()
{
    Super::BeginPlay();
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
    if (Player)
    {
        bIsActive = true;
        Player->SetCheckpointLocation(GetActorLocation());

        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Checkpoint Activated!"));
    }
}
