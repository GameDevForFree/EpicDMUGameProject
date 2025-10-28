#include "ButtonSpawnPlatPress.h"
#include "PlatformSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

AButtonSpawnPlatPress::AButtonSpawnPlatPress()
{
    PrimaryActorTick.bCanEverTick = false;

    
    ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
    RootComponent = ButtonMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/Button_Pressed/Button_Pressed.Button_Pressed")
    );

    if (MeshAsset.Succeeded())
    {
        ButtonMesh->SetStaticMesh(MeshAsset.Object);
        ButtonMesh->SetVisibility(true);
        ButtonMesh->SetWorldScale3D(FVector(1.f));
    }

   
    ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonTrigger"));
    ButtonTrigger->SetupAttachment(RootComponent);
    ButtonTrigger->SetBoxExtent(FVector(50.f, 50.f, 40.f));
    ButtonTrigger->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
    ButtonTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ButtonTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);
    ButtonTrigger->SetGenerateOverlapEvents(true);

    ButtonTrigger->OnComponentBeginOverlap.AddDynamic(this, &AButtonSpawnPlatPress::OnMeshBeginOverlap);

    
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/platformclick1sfx.platformclick1sfx"));
    if (SoundAsset.Succeeded())
        ButtonPushSFX = SoundAsset.Object;

    bPlatformHasSpawned = false;
}

void AButtonSpawnPlatPress::BeginPlay()
{
    Super::BeginPlay();
    ButtonMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("ButtonSpawnPlatPress ready."));
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
    if (bPlatformHasSpawned || !OtherActor || OtherActor == this)
        return;

    
    if (ButtonPushSFX)
        UGameplayStatics::PlaySoundAtLocation(this, ButtonPushSFX, GetActorLocation());

    
    if (UWorld* World = GetWorld())
    {
        const FVector SpawnPos = SpawnLocation;;
        const FRotator SpawnRot = SpawnRotation;

        
        APlatformSpawner* Spawner = World->SpawnActor<APlatformSpawner>(APlatformSpawner::StaticClass(), SpawnPos, SpawnRot);

        if (Spawner && GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("PlatformSpawner spawned successfully!"));
        }
        else if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("PlatformSpawner failed to spawn."));
        }
    }

    bPlatformHasSpawned = true;
    ButtonTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
