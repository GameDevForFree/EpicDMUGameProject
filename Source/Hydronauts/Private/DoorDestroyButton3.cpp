// All code here is by Alex Robertson P2607829

#include "DoorDestroyButton3.h"
#include "DestroyableDoor3.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

ADoorDestroyButton3::ADoorDestroyButton3()
{
    PrimaryActorTick.bCanEverTick = false;

    // creates a mesh component 
    ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
    RootComponent = ButtonMesh;

    // loads the 3D mesh onto the component with the given file path
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/Project_Assets_FBX_OBJ/PowerUp_ButtonSpawnObjects/Button_Pressed/Button_Pressed.Button_Pressed")
    );

    // sets the mesh as the root component of the actor, sets visibility to true and initialises it's default size 
    if (MeshAsset.Succeeded())
    {
        ButtonMesh->SetStaticMesh(MeshAsset.Object);
        ButtonMesh->SetVisibility(true);
        ButtonMesh->SetWorldScale3D(FVector(1.f));
    }

    // creates a box component that will detect overlaps
    ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonTrigger"));
    ButtonTrigger->SetupAttachment(RootComponent);
    ButtonTrigger->SetBoxExtent(FVector(50.f)); // sets box extent
    // links the overlap event onto ButtonTrigger
    ButtonTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADoorDestroyButton3::OnOverlap);

    // finds specified audio file and assigns it to the variable which is a SoundAsset object
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/woodsfx.woodsfx"));
    if (SoundAsset.Succeeded())
        ButtonPushSFX = SoundAsset.Object;
}

// when something overlaps the button triggerbox, this function is called automatically. It also has info on what overlapped it

void ADoorDestroyButton3::OnOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return; // early exit if nothing is overlapping or self-overlap

    UWorld* World = GetWorld(); // gets a reference to the world and exits if the world is invalid
    if (!World) return;

    // finds all door actors of class ADestroyableDoor currently in the level then stores them in an array

    TArray<AActor*> FoundDoors;
    UGameplayStatics::GetAllActorsOfClass(World, ADestroyableDoor3::StaticClass(), FoundDoors);

    // loops through all the found doors and checks if any of the doors has the tag "MainDoor3".
    // Plays the button sfx at the button's location & destroys all doors with the MainDoor3 tag and breaks the loop.
    for (AActor* Door : FoundDoors)
    {
        if (Door->ActorHasTag("MainDoor3"))
        {
            if (ButtonPushSFX)
                UGameplayStatics::PlaySoundAtLocation(this, ButtonPushSFX, GetActorLocation());

            Door->Destroy();

            break;
        }
    }

    ButtonTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision); // disables the trigger box after the first overlap
}
