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

public:
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlatformMesh;
};
