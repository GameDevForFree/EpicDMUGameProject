// This is all code by Michael Threlfall P2797637

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SharkAIController.generated.h"

/**
 * 
 */
UCLASS()
class HYDRONAUTS_API ASharkAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	APawn* PlayerPawn;
};