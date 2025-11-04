// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyableDoor.generated.h"

UCLASS()
class HYDRONAUTS_API ADestroyableDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyableDoor();

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
