#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class HYDRONAUTS_API ACheckpoint : public AActor
{
    GENERATED_BODY()

public:
    ACheckpoint();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UStaticMeshComponent* CheckpointMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UBoxComponent* TriggerBox;

    // Whether this checkpoint has been activated
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsActive;

    virtual void BeginPlay() override;

public:
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
