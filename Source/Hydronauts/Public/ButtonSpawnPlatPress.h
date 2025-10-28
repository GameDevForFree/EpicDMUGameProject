#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonSpawnPlatPress.generated.h"

UCLASS()
class HYDRONAUTS_API AButtonSpawnPlatPress : public AActor
{
    GENERATED_BODY()

public:
    AButtonSpawnPlatPress();

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
    FVector SpawnLocation = FVector(1160.f, 1190.f, 200.f);

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* ButtonMesh;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* ButtonTrigger;

    UPROPERTY(EditAnywhere)
    USoundBase* ButtonPushSFX;

    bool bPlatformHasSpawned = false;
};
