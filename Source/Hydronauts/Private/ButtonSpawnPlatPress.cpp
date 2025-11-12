// All code here is by Alex Robertson P2607829

#include "ButtonSpawnPlatPress.h"
#include "PlatformSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

AButtonSpawnPlatPress::AButtonSpawnPlatPress()
{
    PrimaryActorTick.bCanEverTick = false;

    // creates a mesh component and sets it as the root component of the actor
    
    ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
    RootComponent = ButtonMesh;

    // loads the 3D mesh onto the component with the given file path

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/Button_Pressed/Button_Pressed.Button_Pressed")
    );

    // sets the mesh to component if successful, sets visiblity and scale also

    if (MeshAsset.Succeeded())
    {
        ButtonMesh->SetStaticMesh(MeshAsset.Object);
        ButtonMesh->SetVisibility(true);
        ButtonMesh->SetWorldScale3D(FVector(1.f));
    }

    // creates a box component that will detect overlaps
   
    ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonTrigger"));
    ButtonTrigger->SetupAttachment(RootComponent);

    // creates the size and extent of the "triggerbox" around the button

    ButtonTrigger->SetBoxExtent(FVector(50.f, 50.f, 40.f));
    ButtonTrigger->SetRelativeLocation(FVector(0.f, 0.f, 20.f));

    // disables physics collisions and to only detect when something overlaps it, like a player

    ButtonTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);
    ButtonTrigger->SetGenerateOverlapEvents(true);

    // links the overlap event onto ButtonTrigger

    ButtonTrigger->OnComponentBeginOverlap.AddDynamic(this, &AButtonSpawnPlatPress::OnMeshBeginOverlap);

    // finds specified audio file and assigns it to the variable which is a SoundAsset object
    
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/platformclick1sfx.platformclick1sfx"));
    if (SoundAsset.Succeeded())
        ButtonPushSFX = SoundAsset.Object;

    bPlatformHasSpawned = false; // sets the platform to be spawned only once when the button is pressed
}

void AButtonSpawnPlatPress::BeginPlay()
{
    Super::BeginPlay();
    ButtonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // disables collisions on the mesh, so only the triggerbox detects overlaps
}

// when something overlaps the triggerbox, this function is called automatically. It also has info on what overlapped it

void AButtonSpawnPlatPress::OnMeshBeginOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    // disables button function if any of these states are enabled 

    if (bPlatformHasSpawned || !OtherActor || OtherActor == this)
        return;

    // plays the audio at the actor's position 

    if (ButtonPushSFX)
        UGameplayStatics::PlaySoundAtLocation(this, ButtonPushSFX, GetActorLocation());

    
    // fetches the current world, then uses SpawnLocation and Rotation to spawn the platform at that world location using the separate referenced PlatformSpawner script

    if (UWorld* World = GetWorld())
    {
        const FVector SpawnPos = SpawnLocation;;
        const FRotator SpawnRot = SpawnRotation;

        
        APlatformSpawner* Spawner = World->SpawnActor<APlatformSpawner>(APlatformSpawner::StaticClass(), SpawnPos, SpawnRot);
    }

    bPlatformHasSpawned = true; // flags the platform as spawned so it won't spawn again
    ButtonTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision); // disables the trigger so the button can’t be pressed again
}
