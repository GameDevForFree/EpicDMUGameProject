#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorDestroyButton.generated.h"

UCLASS()
class HYDRONAUTS_API ADoorDestroyButton : public AActor
{
    GENERATED_BODY()

public:
    ADoorDestroyButton();

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
