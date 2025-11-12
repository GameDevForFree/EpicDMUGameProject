// All code here is by Alex Robertson P2607829

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpeed.generated.h"

UCLASS()
class HYDRONAUTS_API APowerUpSpeed : public AActor
{
    GENERATED_BODY()

public:
    APowerUpSpeed();

    UFUNCTION()
    void RespawnPowerUp(); // function that respawns the power up


protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // components/variables

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PUSMesh;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* PUSTrigger;

    UPROPERTY(EditAnywhere, Category = "PowerUp")
    float SpeedBoostMultiplier;

    UPROPERTY(EditAnywhere, Category = "PowerUp")
    float SpeedBoostDuration;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* PUSCollectChime;

    // function that runs when something overlaps the trigger

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
