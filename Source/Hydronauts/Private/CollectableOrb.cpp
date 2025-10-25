#include "CollectableOrb.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ACollectableOrb::ACollectableOrb()
{
    PrimaryActorTick.bCanEverTick = true;

    OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbMesh"));
    RootComponent = OrbMesh;

    OrbTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("OrbTrigger"));
    OrbTrigger->SetupAttachment(OrbMesh);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Relic_Orb"));
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/orbsfx"));

    if (MeshAsset.Succeeded()) OrbMesh->SetStaticMesh(MeshAsset.Object);
    if (SoundAsset.Succeeded()) OrbCollectChime = SoundAsset.Object;
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

    float Time = GetGameTimeSinceCreation();


    FVector OrbLocation = GetActorLocation();
    OrbLocation.Z += FMath::Sin(Time * 2.f) * 20.f * DeltaTime;
    SetActorLocation(OrbLocation);


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
        UGameplayStatics::PlaySoundAtLocation(this, OrbCollectChime, GetActorLocation());
        Destroy();

        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
            FString::Printf(TEXT("50+"), *OtherActor->GetName()));
    }
}
