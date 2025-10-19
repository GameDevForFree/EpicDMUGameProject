// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AStartPositions.generated.h"

/**
 * 
 */
UCLASS()
class HYDRONAUTS_API AAStartPositions : public AActor
{
	GENERATED_BODY()

public:
	// set the default when object is called for the first time
	AAStartPositions();

	UPROPERTY(EditAnywhere, Category = "VALUE")
	int PlayerCount = 0;

protected:
	//called when the game starts or when instantiated
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "StartPositions")
	TSubclassOf<UObject> PlayerSpawnActor;

	UPROPERTY(EditAnywhere, Category = "StartPositions")
	TArray<AActor*> SpawnLocations;

	UFUNCTION(BlueprintCallable, Category = "StartPositions")
	void BeginStartPositions();

	
};
