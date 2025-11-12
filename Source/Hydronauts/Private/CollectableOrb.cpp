// All code here is by Alex Robertson P2607829

#include "CollectableOrb.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "ScoreManager.h"
#include "EngineUtils.h" 

ACollectableOrb::ACollectableOrb()
{
    PrimaryActorTick.bCanEverTick = true;

    
    // creates a mesh component and sets it as the root component of the actor

    OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbMesh"));
    RootComponent = OrbMesh;

    // creates a box component that will detect overlaps

    OrbTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("OrbTrigger"));
    OrbTrigger->SetupAttachment(OrbMesh);

    // loads the 3D mesh onto the component with the given file path

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Project_Assets_FBX_OBJ/Collectable/Relic_Orb/Relic_Orb.Relic_Orb"));

    // finds specified audio file 
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/orbsfx.orbsfx"));

    // sets the mesh to component if successful
    if (MeshAsset.Succeeded())
        OrbMesh->SetStaticMesh(MeshAsset.Object);

    // found audio file is assigned to a variable which is a SoundAsset object
    if (SoundAsset.Succeeded())
        OrbCollectChime = SoundAsset.Object;
}

void ACollectableOrb::BeginPlay()
{
    Super::BeginPlay();

    OrbTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACollectableOrb::OnMeshBeginOverlap); // links the overlap event onto OrbTrigger
    OrbTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // enables collision detection only for overlaps
    OrbMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // disables the visible 3D meshes collision 
}

void ACollectableOrb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

   
    float Time = GetGameTimeSinceCreation(); // acquires how many seconds the orb has existed ingame 
    FVector OrbLocation = GetActorLocation(); // stores the current position of the orb
    OrbLocation.Z += FMath::Sin(Time * 2.f) * 20.f * DeltaTime; // hovers the orb up and down smoothly using a sine wave with delta time keeping it frame rate independent 
    SetActorLocation(OrbLocation); // Applies the new floating position to the orb in the world

   
    AddActorLocalRotation(FRotator(0.f, 45.f * DeltaTime, 0.f)); // Spins the orb continuously on it's Y axis. 
}

// when something overlaps the triggerbox, this function is called automatically. It also has info on what overlapped it

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
        
        if (OrbCollectChime) // plays the audio at the actor's position 
            UGameplayStatics::PlaySoundAtLocation(this, OrbCollectChime, GetActorLocation());

        
        // Enables the usage of the AddScore() function of the ScoreManager class. That displays the game score on a blueprint HUD widget ingame. 

        for (TActorIterator<AScoreManager> It(GetWorld()); It; ++It)
        {
            It->AddScore(50); 
            break;
        }

        
        Destroy(); // destroys the orb after player actor overlaps through it.  
    }
}
