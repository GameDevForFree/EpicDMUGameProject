// All code here is by Alex Robertson P2607829

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioTunnels.generated.h"

UCLASS()
class HYDRONAUTS_API AAudioTunnels : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAudioTunnels(); 

protected:
	
	virtual void BeginPlay() override;

	// components/variables

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* AudioTunnelSFX;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* AudioMesh;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
