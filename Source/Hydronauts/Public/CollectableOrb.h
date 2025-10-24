#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableOrb.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
//class FINALBUTTONPRESSTEST_API ACollectableOrb : public AActor
class HYDRONAUTS_API ACollectableOrb : public AActor
{
    GENERATED_BODY()

public:
    ACollectableOrb();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* OrbMesh;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* OrbTrigger;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* OrbCollectChime;

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
