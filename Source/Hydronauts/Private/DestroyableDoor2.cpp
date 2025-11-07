#include "DestroyableDoor2.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"


ADestroyableDoor2::ADestroyableDoor2()
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

void ADestroyableDoor2::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = GetActorLocation();
}

void ADestroyableDoor2::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADestroyableDoor2::DoorToSpawnAt(const FVector& Location, const FRotator& Rotation)
{
    if (UWorld* World = GetWorld())
    {
        AActor* SpawnedDoor = World->SpawnActor<AActor>(DoorToSpawn, Location, Rotation);

        if (SpawnedDoor)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
                    FString::Printf(TEXT("Door2 spawned successfully: %s"), *SpawnedDoor->GetName()));
            }
        }
    }
}
