#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorDestroyButton3.generated.h"

UCLASS()
class HYDRONAUTS_API ADoorDestroyButton3 : public AActor
{
    GENERATED_BODY()

public:
    ADoorDestroyButton3();

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* ButtonMesh;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* ButtonTrigger;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundBase* ButtonPushSFX;

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
