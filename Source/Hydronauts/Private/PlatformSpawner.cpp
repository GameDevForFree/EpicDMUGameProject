#include "PlatformSpawner.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

APlatformSpawner::APlatformSpawner()
{
    PrimaryActorTick.bCanEverTick = true;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/LandingPad/landingpad_large")
    );

    if (MeshAsset.Succeeded())
    {
        PlatformMesh->SetStaticMesh(MeshAsset.Object);
        PlatformMesh->SetWorldScale3D(FVector(2.f, 2.f, 0.2f));
    }

    RunningTime = 0.f;
}

void APlatformSpawner::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = GetActorLocation();
}

void APlatformSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    RunningTime += DeltaTime;

    
    float DeltaZ = FMath::Sin(RunningTime * HoverSpeed * 2 * PI) * HoverAmplitude;
    FVector NewLocation = StartLocation;
    NewLocation.Z += DeltaZ;
    SetActorLocation(NewLocation);

    
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += RotationSpeed * DeltaTime;
    SetActorRotation(NewRotation);
}

void APlatformSpawner::SpawnPlatformAt(const FVector& Location, const FRotator& Rotation)
{

    if (UWorld* World = GetWorld())
    {
        AActor* SpawnedPlatform = World->SpawnActor<AActor>(PlatformToSpawn, Location, Rotation);

        if (SpawnedPlatform)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
                    FString::Printf(TEXT("Platform spawned successfully: %s"), *SpawnedPlatform->GetName()));
            }
        }
  
        }
    }
