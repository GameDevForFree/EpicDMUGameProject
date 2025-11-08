#include "CollectableOrb.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "ScoreManager.h"
#include "EngineUtils.h" // for TActorIterator

ACollectableOrb::ACollectableOrb()
{
    PrimaryActorTick.bCanEverTick = true;

    // Mesh
    OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbMesh"));
    RootComponent = OrbMesh;

    // Trigger
    OrbTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("OrbTrigger"));
    OrbTrigger->SetupAttachment(OrbMesh);

    // Load mesh and sound
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Project_Assets_FBX_OBJ/Collectable/Relic_Orb/Relic_Orb.Relic_Orb"));
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/orbsfx.orbsfx"));

    if (MeshAsset.Succeeded())
        OrbMesh->SetStaticMesh(MeshAsset.Object);

    if (SoundAsset.Succeeded())
        OrbCollectChime = SoundAsset.Object;
}

void ACollectableOrb::BeginPlay()
{
    Super::BeginPlay();

    OrbTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACollectableOrb::OnMeshBeginOverlap);
    OrbTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    OrbMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACollectableOrb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Floating effect
    float Time = GetGameTimeSinceCreation();
    FVector OrbLocation = GetActorLocation();
    OrbLocation.Z += FMath::Sin(Time * 2.f) * 20.f * DeltaTime;
    SetActorLocation(OrbLocation);

    // Rotate
    AddActorLocalRotation(FRotator(0.f, 45.f * DeltaTime, 0.f));
}

void ACollectableOrb::OnMeshBeginOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        // Play collect sound
        if (OrbCollectChime)
            UGameplayStatics::PlaySoundAtLocation(this, OrbCollectChime, GetActorLocation());

        // Add 50 points to the first ScoreManager found
        for (TActorIterator<AScoreManager> It(GetWorld()); It; ++It)
        {
            It->AddScore(50); // updates both variable and HUD
            break; // only use the first ScoreManager
        }

        // Destroy the orb
        Destroy();
    }
}
