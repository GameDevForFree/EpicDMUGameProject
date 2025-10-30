// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveMachine.generated.h"

UCLASS()
class HYDRONAUTS_API AWaveMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveMachine();

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WaveData", meta = (ExposeOnSpawn = "true", MakeEditWidget = "true"))
	int WaveAmountLength = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WaveData", meta = (ExposeOnSpawn = "true", MakeEditWidget = "true"))
	int WaveAmountWidth = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WaveData", meta = (ExposeOnSpawn = "true", MakeEditWidget = "true"))
	float DistanceBetweenWaves = 50.f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Array of quads
	TArray<FVector*> QuadArray;
	//time handle
	FTimerHandle* timer;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//displaces the Y postion based on time and relative world position
	void ApplyWave(FVector& wave);

	void Draw();
};
