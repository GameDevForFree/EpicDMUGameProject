#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class HYDRONAUTS_API APlatformSpawner : public AActor
{
    GENERATED_BODY()

public:
    APlatformSpawner();

    virtual void Tick(float DeltaTime) override;  

    UFUNCTION(BlueprintCallable, Category = "Platform Spawning")
    void SpawnPlatformAt(const FVector& Location, const FRotator& Rotation);

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Spawning")
    TSubclassOf<AActor> PlatformToSpawn;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlatformMesh;

    
    UPROPERTY(EditAnywhere, Category = "Hover Settings")
    float HoverAmplitude = 20.f; 

    UPROPERTY(EditAnywhere, Category = "Hover Settings")
    float HoverSpeed = 0.5f;       

    UPROPERTY(EditAnywhere, Category = "Rotation Settings")
    float RotationSpeed = 20.f;   

private:
    FVector StartLocation;
    float RunningTime;
};
