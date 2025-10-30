// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveMachine.h"

// Sets default values
AWaveMachine::AWaveMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	timer = new FTimerHandle();

}

// Called when the game starts or when spawned
void AWaveMachine::BeginPlay()
{
	Super::BeginPlay();

	int i, j;

	for (i = 0; i < WaveAmountLength; i++) 
	{
		for (j = 0; j < WaveAmountWidth; j++) 
		{
			QuadArray.Add(new FVector(
				(float)i * DistanceBetweenWaves,
				(float)j * DistanceBetweenWaves,
				0
				)
			);
		}
	}
}

// Called every frame
void AWaveMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto i = QuadArray.begin(); i != QuadArray.end(); ++i)
	{
		ApplyWave(**i);
	}

	Draw();
}

void AWaveMachine::ApplyWave(FVector& wave)
{
	wave = FVector(wave.X, wave.Y, sinh(wave.Y)+cosh(wave.X));
}

void AWaveMachine::Draw()
{
	for (auto i = QuadArray.begin(); i != QuadArray.end(); ++i)
	{
		DrawDebugSphere(GetWorld(),**i, 10.f, 6, FColor::Blue);
	}
}

