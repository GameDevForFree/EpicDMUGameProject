#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "GameTimer.generated.h"

class UTextBlock;

UCLASS()
class HYDRONAUTS_API AGameTimer : public AActor
{
    GENERATED_BODY()

public:
    AGameTimer();

protected:
    virtual void BeginPlay() override;

private:
    void UpdateHUD();
    void EndGame();

    // Timer
    FTimerHandle CountdownHandle;
    float TimeRemaining; // in seconds

    // HUD
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> TimerWidgetClass; // assign WBP_ScoreHUD in Editor

    UUserWidget* TimerWidgetInstance;
    UTextBlock* TimerTextBlock;
};
