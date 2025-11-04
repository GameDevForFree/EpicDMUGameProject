// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelWavepoint.h"
#include "MainCharacter.h"
//#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelWavepoint::ALevelWavepoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creating the box triggers
	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	Volume->InitBoxExtent(FVector(100.f, 400.f, 500.f));
	Volume->SetCollisionResponseToAllChannels(ECR_Overlap);
	Volume->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ALevelWavepoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelWavepoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelWavepoint::PostInitializeComponents() 
{
	Super::PostInitializeComponents();

	Volume->OnComponentBeginOverlap.AddDynamic(this, &ALevelWavepoint::OnVolumeBeginOverlap);
	Volume->OnComponentEndOverlap.AddDynamic(this, &ALevelWavepoint::OnVolumeEndOverlap);
}

void ALevelWavepoint::OnVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor))
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("added rotation")));
		////adds the level to a list
		//GetWorld()->AddLevel(NextLevel);
		////removed the current level from the list, forcing the player into the next one
		//GetWorld()->RemoveLevel(GetWorld()->GetCurrentLevel());
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("detected collision")));
}

void ALevelWavepoint::OnVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//triggers on collision exit
}

