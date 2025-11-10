// All code by Michael Threfall P2797637

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SharkAIController2.generated.h"

/**
 * 
 */
UCLASS()
class HYDRONAUTS_API ASharkAIController2 : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	APawn* PlayerPawn;
};
