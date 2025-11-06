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

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* ButtonMesh;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* ButtonTrigger;

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
