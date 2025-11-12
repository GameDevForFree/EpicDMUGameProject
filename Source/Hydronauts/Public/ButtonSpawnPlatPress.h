// All code here is by Alex Robertson P2607829

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

    UFUNCTION()   // created an overlap function that unreal can call
    void OnMeshBeginOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    // allows the platform to be spawned where chosen with the given XYZ coordinates in the editor 
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Spawning")
    FVector SpawnLocation = FVector(0.f, 0.f, 0.f);

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Spawning")
    FRotator SpawnRotation = FRotator::ZeroRotator;

    // components/variables

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* ButtonMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UBoxComponent* ButtonTrigger;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundBase* ButtonPushSFX;

    bool bPlatformHasSpawned;
};
