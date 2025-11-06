#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyableDoor2.generated.h"

UCLASS()
class HYDRONAUTS_API ADestroyableDoor2 : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADestroyableDoor2();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
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
