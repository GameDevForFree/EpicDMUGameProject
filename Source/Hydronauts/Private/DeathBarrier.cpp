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
    PrimaryActorTick.bCanEverTick = false;

    KillZone = CreateDefaultSubobject<UBoxComponent>(TEXT("KillZone"));
    RootComponent = KillZone;

    KillZone->InitBoxExtent(FVector(200.f, 200.f, 100.f));
    KillZone->SetCollisionProfileName(TEXT("Trigger"));
    KillZone->SetGenerateOverlapEvents(true);

    BarrierMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrierMesh"));
    BarrierMesh->SetupAttachment(RootComponent);
    BarrierMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BarrierMesh->SetRelativeScale3D(FVector(1.f));

    KillZone->OnComponentBeginOverlap.AddDynamic(this, &ADeathBarrier::OnOverlapBegin);
}

void ADeathBarrier::BeginPlay()
{
    Super::BeginPlay();
}

void ADeathBarrier::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
    if (Player)
    {
        
        Player->RespawnAtCheckpoint();

       
        AScoreManager* ScoreManager = Cast<AScoreManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AScoreManager::StaticClass()));
        if (ScoreManager)
        {
            ScoreManager->SubtractScore(15); 
        }
    }
}
