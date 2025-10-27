#include "PowerUpSpeed.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

APowerUpSpeed::APowerUpSpeed()
{
    PrimaryActorTick.bCanEverTick = true;


    PUSMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PUSMesh"));
    RootComponent = PUSMesh;


    PUSTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PUSTrigger"));
    PUSTrigger->SetupAttachment(PUSMesh);
    PUSTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PUSTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);


    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/SpeedUpStar/Star1"));
    if (MeshAsset.Succeeded())
    {
        PUSMesh->SetStaticMesh(MeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/speedupsfx"));
    if (SoundAsset.Succeeded())
    {
        PUSCollectChime = SoundAsset.Object;
    }


    SpeedBoostMultiplier = 2.0f;
    SpeedBoostDuration = 4.0f;
}

void APowerUpSpeed::BeginPlay()
{
    Super::BeginPlay();

    PUSTrigger->OnComponentBeginOverlap.AddDynamic(this, &APowerUpSpeed::OnOverlap);
    PUSTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PUSMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APowerUpSpeed::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    float Time = GetGameTimeSinceCreation();
    FVector Loc = GetActorLocation();
    Loc.Z += FMath::Sin(Time * 2.f) * 20.f * DeltaTime;
    SetActorLocation(Loc);

    AddActorLocalRotation(FRotator(0.f, 45.f * DeltaTime, 0.f));
}

void APowerUpSpeed::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacter* Player = Cast<ACharacter>(OtherActor);
    if (!Player) return;

    if (PUSCollectChime)
    {
        UGameplayStatics::PlaySoundAtLocation(this, PUSCollectChime, GetActorLocation());
    }

    if (UCharacterMovementComponent* Move = Player->GetCharacterMovement())
    {

        float OriginalSpeed = Move->MaxWalkSpeed;
        Move->MaxWalkSpeed *= SpeedBoostMultiplier;


        FTimerHandle ResetHandle;
        FTimerDelegate ResetDelegate;

        ResetDelegate.BindLambda([Player, OriginalSpeed]()
            {
                if (Player && Player->GetCharacterMovement())
                {
                    Player->GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed;
                }
            });

        Player->GetWorldTimerManager().SetTimer(ResetHandle, ResetDelegate, SpeedBoostDuration, false);
    }

    Destroy();
}
