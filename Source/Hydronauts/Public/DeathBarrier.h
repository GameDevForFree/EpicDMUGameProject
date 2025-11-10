#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HydroSaveGame.h"
#include "DeathBarrier.generated.h"

UCLASS()
class HYDRONAUTS_API ADeathBarrier : public AActor
{
    GENERATED_BODY()

public:
    ADeathBarrier();

protected:
  
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Death Barrier")
    class UBoxComponent* KillZone;

   
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Death Barrier")
    class UStaticMeshComponent* BarrierMesh;

    virtual void BeginPlay() override;

public:
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
