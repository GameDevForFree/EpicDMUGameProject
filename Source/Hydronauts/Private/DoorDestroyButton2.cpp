#include "DoorDestroyButton2.h"
#include "DestroyableDoor2.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

ADoorDestroyButton2::ADoorDestroyButton2()
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
    ButtonTrigger->SetBoxExtent(FVector(50.f));
    ButtonTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADoorDestroyButton2::OnOverlap);

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Audio/woodsfx.woodsfx"));
    if (SoundAsset.Succeeded())
        ButtonPushSFX = SoundAsset.Object;
}

void ADoorDestroyButton2::OnOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    UWorld* World = GetWorld();
    if (!World) return;

    
    TArray<AActor*> FoundDoors;
    UGameplayStatics::GetAllActorsOfClass(World, ADestroyableDoor2::StaticClass(), FoundDoors);

    for (AActor* Door : FoundDoors)
    {
        if (Door->ActorHasTag("MainDoor2"))
        {
            if (ButtonPushSFX)
                UGameplayStatics::PlaySoundAtLocation(this, ButtonPushSFX, GetActorLocation());

            Door->Destroy();

            break;
        }
    }

    
    ButtonTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
