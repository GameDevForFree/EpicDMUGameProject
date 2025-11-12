// All code here is by Alex Robertson P2607829

#include "PlatformSpawner.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

APlatformSpawner::APlatformSpawner()
{
    PrimaryActorTick.bCanEverTick = true;

    // creates a mesh component and sets it as the root component of the actor

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;

    // loads the 3D mesh onto the component with the given file path

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/LandingPad/landingpad_large")
    );

    // sets the mesh to component if successful & sets it's world scale

    if (MeshAsset.Succeeded())
    {
        PlatformMesh->SetStaticMesh(MeshAsset.Object);
        PlatformMesh->SetWorldScale3D(FVector(1.f, 1.f, 0.5f));
    }

    RunningTime = 0.f; // initializes the running time for hover calculations
}

void APlatformSpawner::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = GetActorLocation(); // stores the actor’s starting location so the hover oscillation can be relative to it
}

void APlatformSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    RunningTime += DeltaTime; // adds elapsed time to RunningTime every frame


    // calculates a vertical sine wave oscillation for hover movement & updates the actor's location using that offset
    
    float DeltaZ = FMath::Sin(RunningTime * HoverSpeed * 2 * PI) * HoverAmplitude; 
    FVector NewLocation = StartLocation;
    NewLocation.Z += DeltaZ;
    SetActorLocation(NewLocation);

    
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += RotationSpeed * DeltaTime;
    SetActorRotation(NewRotation); // rotates the platform around its Y axis using RotationSpeed
}

// spawns an instance of PlatformToSpawn at a specified location/rotation

void APlatformSpawner::SpawnPlatformAt(const FVector& Location, const FRotator& Rotation)
{

    if (UWorld* World = GetWorld())
    {
        AActor* SpawnedPlatform = World->SpawnActor<AActor>(PlatformToSpawn, Location, Rotation);
  
        }
    }
