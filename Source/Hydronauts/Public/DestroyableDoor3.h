#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyableDoor3.generated.h"

UCLASS()
class HYDRONAUTS_API ADestroyableDoor3 : public AActor
{
    GENERATED_BODY()

public:
    
    ADestroyableDoor3();

protected:
    
    virtual void BeginPlay() override;

public:
   
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Door Spawning")
    void DoorToSpawnAt(const FVector& Location, const FRotator& Rotation);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Spawning")
    TSubclassOf<AActor> DoorToSpawn;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

private:
    FVector StartLocation;
};
