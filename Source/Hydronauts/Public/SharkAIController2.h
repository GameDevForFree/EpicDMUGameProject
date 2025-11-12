// All code by Michael Threfall P2797637

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SharkAIController2.generated.h"

UCLASS()
class HYDRONAUTS_API ASharkAIController2 : public AAIController
{
    GENERATED_BODY()

public:

    ASharkAIController2();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundBase* SharkSFX;

private:
    APawn* PlayerPawn;
    bool bHasPlayedSound = false; // Once the boolean is set to true, the audio will play
};