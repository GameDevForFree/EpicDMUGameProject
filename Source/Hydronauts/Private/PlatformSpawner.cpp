#include "PlatformSpawner.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

APlatformSpawner::APlatformSpawner()
{
    PrimaryActorTick.bCanEverTick = true;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/LandingPad/landingpad_large.landingpad_large"));
    if (MeshAsset.Succeeded())
    {
        PlatformMesh->SetStaticMesh(MeshAsset.Object);
        PlatformMesh->SetWorldScale3D(FVector(2.f, 2.f, 0.2f));
    }
}

void APlatformSpawner::BeginPlay()
{
    Super::BeginPlay();
}

void APlatformSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    float Time = GetGameTimeSinceCreation();
    FVector Loc = GetActorLocation();
    Loc.Z += FMath::Sin(Time * 2.f) * 20.f * DeltaTime;
    SetActorLocation(Loc);

    AddActorLocalRotation(FRotator(0.f, 15.f * DeltaTime, 0.f));
}