#include "CollectableOrb.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

ACollectableOrb::ACollectableOrb()
{
    PrimaryActorTick.bCanEverTick = true;

    OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbMesh"));
    RootComponent = OrbMesh;
    OrbMesh->SetGenerateOverlapEvents(false);

    OrbTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("OrbTrigger"));
    OrbTrigger->SetupAttachment(OrbMesh);
    OrbTrigger->SetBoxExtent(FVector(100.f));
    OrbTrigger->SetGenerateOverlapEvents(true);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/All/Game/Project_Assets_FBX_OBJ/Collectable/Relic_Orb"));
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/All/Game/Audio"));

    if (SoundAsset.Succeeded())
    {
        OrbCollectChime = SoundAsset.Object;
    }

    if (MeshAsset.Succeeded())
    {
        OrbMesh->SetStaticMesh(MeshAsset.Object);

    }

}

void ACollectableOrb::BeginPlay()
{
    Super::BeginPlay();

    OrbTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    OrbTrigger->SetCollisionObjectType(ECC_WorldDynamic);
    OrbTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);
    OrbMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    OrbTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACollectableOrb::OnMeshBeginOverlap);

}

void ACollectableOrb::OnMeshBeginOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {

        Destroy();
        UGameplayStatics::PlaySoundAtLocation(this, OrbCollectChime, GetActorLocation());

    }
}


