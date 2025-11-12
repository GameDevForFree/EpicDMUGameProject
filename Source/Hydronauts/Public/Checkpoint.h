// All code here is by Alex Robertson P2607829

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
    class UStaticMeshComponent* CheckpointMesh; // visible 3D mesh for the checkpoint, viewable only in editor

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UBoxComponent* TriggerBox; // the invisible box that detects overlaps when the player enters

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsActive; // responsible in knowing if the current checkpoint is active or not

    virtual void BeginPlay() override;

    // function that runs when something overlaps the trigger

public:
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
