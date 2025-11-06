#include "DoorDestroyButton3.h"
#include "DestroyableDoor3.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

ADoorDestroyButton3::ADoorDestroyButton3()
{
    PrimaryActorTick.bCanEverTick = false;

    // Mesh
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

    // Trigger box
    ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonTrigger"));
    ButtonTrigger->SetupAttachment(RootComponent);
    ButtonTrigger->SetBoxExtent(FVector(50.f));
    ButtonTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADoorDestroyButton3::OnOverlap);
}

void ADoorDestroyButton3::OnOverlap(
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

    // Find all DestroyableDoor actors
    TArray<AActor*> FoundDoors;
    UGameplayStatics::GetAllActorsOfClass(World, ADestroyableDoor3::StaticClass(), FoundDoors);

    for (AActor* Door : FoundDoors)
    {
        if (Door->ActorHasTag("MainDoor3"))
        {
            Door->Destroy();

            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("MainDoor3 destroyed!"));
            break;
        }
    }

    // Disable trigger after use
    ButtonTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
