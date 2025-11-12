// All code here is by Alex Robertson P2607829

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

    // creates a mesh component and sets it as the root component of the actor

    PUSMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PUSMesh"));
    RootComponent = PUSMesh;

    // creates a box component that will detect overlaps

    PUSTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PUSTrigger"));
    PUSTrigger->SetupAttachment(PUSMesh);
    PUSTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PUSTrigger->SetCollisionResponseToAllChannels(ECR_Overlap);

    // loads the 3D mesh onto the component with the given file path

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/SpeedUpStar/Star1"));
    if (MeshAsset.Succeeded())
    {
        PUSMesh->SetStaticMesh(MeshAsset.Object);
    }

    // finds specified audio file and assigns it to the variable which is a SoundAsset object

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/speedupsfx"));
    if (SoundAsset.Succeeded())
    {
        PUSCollectChime = SoundAsset.Object;
    }

    // sets how much the speed boost multiplies the players speed and the duration of the speed boost

    SpeedBoostMultiplier = 2.0f;
    SpeedBoostDuration = 4.0f;
}

void APowerUpSpeed::BeginPlay()
{
    Super::BeginPlay();

    PUSTrigger->OnComponentBeginOverlap.AddDynamic(this, &APowerUpSpeed::OnOverlap);  // links the overlap event onto PUSTrigger
    PUSTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);  // enables collision detection only for overlaps
    PUSMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // disables the visible 3D meshes collision 
}

void APowerUpSpeed::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // enables the speed boost power up to float up and down using a sine wave for animation

    float Time = GetGameTimeSinceCreation();
    FVector Loc = GetActorLocation();
    Loc.Z += FMath::Sin(Time * 2.f) * 20.f * DeltaTime;
    SetActorLocation(Loc);

    AddActorLocalRotation(FRotator(0.f, 45.f * DeltaTime, 0.f));  // rotates the power up around it's Y axis
}

// allows the power up to respawn after a delay

void APowerUpSpeed::RespawnPowerUp()
{
    PUSMesh->SetVisibility(true);
    PUSTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

// when something overlaps the triggerbox, this function is called automatically. It also has info on what overlapped it

void APowerUpSpeed::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacter* Player = Cast<ACharacter>(OtherActor); // checks if overlapping actor is a player and if not, return
    if (!Player) return;

    if (PUSCollectChime) // plays the audio at the actor's position 
    {
        UGameplayStatics::PlaySoundAtLocation(this, PUSCollectChime, GetActorLocation());
    }

    // gets the player’s movement component and doubles their speed

    if (UCharacterMovementComponent* Move = Player->GetCharacterMovement())
    {

        float OriginalSpeed = Move->MaxWalkSpeed;
        Move->MaxWalkSpeed *= SpeedBoostMultiplier;


        // sets a timer to reset the player’s speed to normal after speed boosting

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

    // hides the power up and disables its trigger after collection
   
    PUSMesh->SetVisibility(false);
    PUSTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // sets a 5 second timer to respawn the power up 
 
    FTimerHandle RespawnHandle;
    GetWorldTimerManager().SetTimer(RespawnHandle, this, &APowerUpSpeed::RespawnPowerUp, 5.0f, false);
}

