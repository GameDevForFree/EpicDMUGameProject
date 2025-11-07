#include "DestroyableDoor3.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"


ADestroyableDoor3::ADestroyableDoor3()
{
    PrimaryActorTick.bCanEverTick = true;

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/Project_Assets_FBX_OBJ/TerrainObjects/Wall_U/Wall_FirstAge.Wall_FirstAge")
    );

    if (MeshAsset.Succeeded())
    {
        DoorMesh->SetStaticMesh(MeshAsset.Object);
        DoorMesh->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
    }
}

void ADestroyableDoor3::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = GetActorLocation();
}

void ADestroyableDoor3::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADestroyableDoor3::DoorToSpawnAt(const FVector& Location, const FRotator& Rotation)
{
    if (UWorld* World = GetWorld())
    {
        AActor* SpawnedDoor = World->SpawnActor<AActor>(DoorToSpawn, Location, Rotation);

        if (SpawnedDoor)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
                    FString::Printf(TEXT("Door3 spawned successfully: %s"), *SpawnedDoor->GetName()));
            }
        }
    }
}
