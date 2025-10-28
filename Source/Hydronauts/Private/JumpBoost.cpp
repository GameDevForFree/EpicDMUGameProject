#include "JumpBoost.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

AJumpBoost::AJumpBoost()
{
    PrimaryActorTick.bCanEverTick = true;


    JBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JBMesh"));
    RootComponent = JBMesh;


    JBTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("JBTrigger"));
    JBTrigger->SetupAttachment(JBMesh);
    JBTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    JBTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);


    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/JumpBoostStar/Star2"));
    if (MeshAsset.Succeeded())
    {
        JBMesh->SetStaticMesh(MeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/speedupsfxend"));
    if (SoundAsset.Succeeded())
    {
        JBCollectChime = SoundAsset.Object;
    }


    JumpBoostMultiplier = 2.0f;
    JumpBoostDuration = 6.0f;
}

void AJumpBoost::BeginPlay()
{
    Super::BeginPlay();

    JBTrigger->OnComponentBeginOverlap.AddDynamic(this, &AJumpBoost::OnOverlap);
    JBTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    JBMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AJumpBoost::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    float Time = GetGameTimeSinceCreation();
    FVector Loc = GetActorLocation();
    Loc.Z += FMath::Sin(Time * 2.f) * 20.f * DeltaTime;
    SetActorLocation(Loc);

    AddActorLocalRotation(FRotator(0.f, 45.f * DeltaTime, 0.f));
}

void AJumpBoost::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacter* Player = Cast<ACharacter>(OtherActor);
    if (!Player) return;


    if (JBCollectChime)
    {
        UGameplayStatics::PlaySoundAtLocation(this, JBCollectChime, GetActorLocation());
    }

    if (UCharacterMovementComponent* Move = Player->GetCharacterMovement())
    {
        float OriginalJumpZVelocity = Move->JumpZVelocity;
        Move->JumpZVelocity *= JumpBoostMultiplier;


        FTimerHandle ResetHandle;
        FTimerDelegate ResetDelegate;

        ResetDelegate.BindLambda([Player, OriginalJumpZVelocity]()
            {
                if (Player && Player->GetCharacterMovement())
                {
                    Player->GetCharacterMovement()->JumpZVelocity = OriginalJumpZVelocity;
                }
            });

        Player->GetWorldTimerManager().SetTimer(ResetHandle, ResetDelegate, JumpBoostDuration, false);
    }


    Destroy();
}