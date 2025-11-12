// All code here is by Alex Robertson P2607829

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableOrb.generated.h"

// tells the compiler these classes exist, speeds things up

class UStaticMeshComponent;
class UBoxComponent;
class USoundBase;

UCLASS()
class HYDRONAUTS_API ACollectableOrb : public AActor
{
    GENERATED_BODY()

public:
    ACollectableOrb();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // components/variables

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* OrbMesh;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* OrbTrigger;

    UPROPERTY(EditAnywhere)
    USoundBase* OrbCollectChime;

    // function that runs when something overlaps the trigger

    UFUNCTION()
    void OnMeshBeginOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};
