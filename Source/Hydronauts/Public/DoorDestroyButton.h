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
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnMeshBeginOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Spawning")
    FVector SpawnLocation = FVector(0.f, 0.f, 0.f);


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Spawning")
    FRotator SpawnRotation = FRotator::ZeroRotator;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* ButtonMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UBoxComponent* ButtonTrigger;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundBase* ButtonPushSFX;

    bool bDoorDestroyed;
};
