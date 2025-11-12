// All code here is by Alex Robertson P2607829

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorDestroyButton2.generated.h"

UCLASS()
class HYDRONAUTS_API ADoorDestroyButton2 : public AActor
{
    GENERATED_BODY()

public:
    ADoorDestroyButton2();

    // components/variables

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* ButtonMesh;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* ButtonTrigger;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundBase* ButtonPushSFX;

    // function that runs when something overlaps the trigger

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
