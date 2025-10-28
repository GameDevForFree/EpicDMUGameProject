#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpBoost.generated.h"

UCLASS()
class HYDRONAUTS_API AJumpBoost : public AActor
{
    GENERATED_BODY()

public:
    AJumpBoost();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* JBMesh;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* JBTrigger;

    UPROPERTY(EditAnywhere, Category = "JumpBoost")
    float JumpBoostMultiplier;

    UPROPERTY(EditAnywhere, Category = "JumpBoost")
    float JumpBoostDuration;

    UPROPERTY(EditAnywhere, Category = "Audio")
    class USoundBase* JBCollectChime;

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};