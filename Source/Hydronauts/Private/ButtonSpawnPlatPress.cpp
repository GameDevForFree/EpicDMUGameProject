#include "ButtonSpawnPlatPress.h"
#include "PlatformSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AButtonSpawnPlatPress::AButtonSpawnPlatPress()
{
    PrimaryActorTick.bCanEverTick = false;

    ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
    RootComponent = ButtonMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/Button_Pressed/Button_Pressed.Button_Pressed"));
    if (MeshAsset.Succeeded())
    {
        ButtonMesh->SetStaticMesh(MeshAsset.Object);
        ButtonMesh->SetVisibility(true);
        ButtonMesh->SetWorldScale3D(FVector(1.f));
    }

    ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonTrigger"));
    ButtonTrigger->SetupAttachment(RootComponent);
    ButtonTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);


    ButtonTrigger->OnComponentBeginOverlap.AddDynamic(this, &AButtonSpawnPlatPress::OnMeshBeginOverlap);

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/platformclick1sfx.platformclick1sfx"));
    if (SoundAsset.Succeeded())
    {
        ButtonPushSFX = SoundAsset.Object;
    }
}

void AButtonSpawnPlatPress::BeginPlay()
{
    Super::BeginPlay();
    ButtonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AButtonSpawnPlatPress::OnMeshBeginOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (bPlatformHasSpawned) return;

    if (OtherActor && OtherActor != this)
    {
        // Optional: spawn relative to button
        const FVector SpawnLoc = GetActorLocation() + SpawnLocation;
        const FRotator SpawnRotation = FRotator::ZeroRotator;
        FActorSpawnParameters SpawnParams;

        if (ButtonPushSFX)
        {
            UGameplayStatics::PlaySoundAtLocation(this, ButtonPushSFX, GetActorLocation());
        }

        if (UWorld* World = GetWorld())
        {
            World->SpawnActor<APlatformSpawner>(APlatformSpawner::StaticClass(), SpawnLoc, SpawnRotation, SpawnParams);
        }

        bPlatformHasSpawned = true;
        ButtonTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}
