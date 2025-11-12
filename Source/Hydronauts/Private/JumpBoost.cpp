// All code here is by Alex Robertson P2607829

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


    // creates a mesh component and sets it as the root component of the actor

    JBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JBMesh"));
    RootComponent = JBMesh;

    // creates a box component that will detect overlaps

    JBTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("JBTrigger"));
    JBTrigger->SetupAttachment(JBMesh);
    JBTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    JBTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);

    // loads the 3D mesh onto the component with the given file path

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/JumpBoostStar/Star2"));
    if (MeshAsset.Succeeded())
    {
        JBMesh->SetStaticMesh(MeshAsset.Object);
    }

    // finds specified audio file and assigns it to the variable which is a SoundAsset object

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/speedupsfxend"));
    if (SoundAsset.Succeeded())
    {
        JBCollectChime = SoundAsset.Object;
    }

    // sets how much the jump boost multiplies the players jump and the duration of the jump boost

    JumpBoostMultiplier = 2.0f;
    JumpBoostDuration = 4.0f;
}

void AJumpBoost::BeginPlay()
{
    Super::BeginPlay();

    JBTrigger->OnComponentBeginOverlap.AddDynamic(this, &AJumpBoost::OnOverlap); // links the overlap event onto JBTrigger
    JBTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // enables collision detection only for overlaps
    JBMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // disables the visible 3D meshes collision 
}

void AJumpBoost::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // enables the jump boost power up to float up and down using a sine wave for animation

    float Time = GetGameTimeSinceCreation();
    FVector Loc = GetActorLocation();
    Loc.Z += FMath::Sin(Time * 2.f) * 20.f * DeltaTime;
    SetActorLocation(Loc);

    AddActorLocalRotation(FRotator(0.f, 45.f * DeltaTime, 0.f)); // rotates the power up around it's Y axis
}

// allows the power up to respawn after a delay

void AJumpBoost::RespawnPowerUp()
{
    JBMesh->SetVisibility(true);
    JBTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

// when something overlaps the triggerbox, this function is called automatically. It also has info on what overlapped it

void AJumpBoost::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacter* Player = Cast<ACharacter>(OtherActor); // checks if overlapping actor is a player and if not, return
    if (!Player) return;


    if (JBCollectChime) // plays the audio at the actor's position 
    {
        UGameplayStatics::PlaySoundAtLocation(this, JBCollectChime, GetActorLocation());
    }

    // fetches the player's movement component and boosts their jump velocity for the duration of the power up

    if (UCharacterMovementComponent* Move = Player->GetCharacterMovement())
    {
        float OriginalJumpZVelocity = Move->JumpZVelocity;
        Move->JumpZVelocity *= JumpBoostMultiplier;


        // sets a timer to reset the player’s jump to normal after jump boosting

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

    // hides the power up and disables its trigger after collection

    JBMesh->SetVisibility(false);
    JBTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // sets a 5 second timer to respawn the power up 

    FTimerHandle RespawnHandle;
    GetWorldTimerManager().SetTimer(RespawnHandle, this, &AJumpBoost::RespawnPowerUp, 5.0f, false);
}
