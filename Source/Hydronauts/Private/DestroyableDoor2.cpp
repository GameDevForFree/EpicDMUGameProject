// All code here is by Alex Robertson P2607829

#include "DestroyableDoor2.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"


ADestroyableDoor2::ADestroyableDoor2()
{

    PrimaryActorTick.bCanEverTick = true;

    // creates a mesh component and sets it as the root component of the actor

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    // loads the 3D mesh onto the component with the given file path

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/Project_Assets_FBX_OBJ/TerrainObjects/Wall_U/Wall_FirstAge.Wall_FirstAge")
    );

    // sets the mesh to component if successful and scales it twice its size

    if (MeshAsset.Succeeded())
    {
        DoorMesh->SetStaticMesh(MeshAsset.Object);
        DoorMesh->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
    }

}

void ADestroyableDoor2::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = GetActorLocation(); // gets the actor location at the start

}

void ADestroyableDoor2::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// ---------------------------- OLD REMNANT CODE LEFT BEHIND / TOO LATE IN DEVELOPMENT TO REMOVE IN FEAR OF BREAKING SOMETHING 
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
                    FString::Printf(TEXT("Door spawned successfully: %s"), *SpawnedDoor->GetName()));
            }
        }

    }
}
