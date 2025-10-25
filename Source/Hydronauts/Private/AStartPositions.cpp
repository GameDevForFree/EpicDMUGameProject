// Fill out your copyright notice in the Description page of Project Settings.


#include "AStartPositions.h"

AAStartPositions::AAStartPositions()
{
	
}

void AAStartPositions::BeginPlay()
{
	Super::BeginPlay();

	BeginStartPositions();

}

void AAStartPositions::Tick(float DeltaTime)
{
}

void AAStartPositions::BeginStartPositions()
{
	FTimerHandle MyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, [&]()
	{
		UE_LOG(LogTemp, Warning, TEXT("This text will appear in the console 3 seconds after execution"));
		for (int item = 0; item < SpawnLocations.Num(); item++)
		{
			FVector Offset = (FVector::UpVector * 15.0f);

			FVector ActorTransformLoc = SpawnLocations[item]->GetActorLocation();
			FVector ActorSpawnLoc = ActorTransformLoc + Offset;

			for (int SpawnedPlayer = 0; SpawnedPlayer < PlayerCount; SpawnedPlayer++)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Through Loop")));

				UObject* PlayerSpawn = GetWorld()->SpawnActor<UObject>(PlayerSpawnActor, ActorSpawnLoc, GetActorRotation());
				
			}
		};
	}, 3, false);
}