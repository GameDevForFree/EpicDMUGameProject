// All code here is by Alex Robertson P2607829

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

	// ---------------------------- OLD REMNANT CODE LEFT BEHIND / TOO LATE IN DEVELOPMENT TO REMOVE IN FEAR OF BREAKING SOMETHING 

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
