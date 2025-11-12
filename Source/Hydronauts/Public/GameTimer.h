// // All code by Michael Threfall P2797637 with assistance from Alex Robertson P2607829

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

    // two private void declarations for updating the timer and for ending the game

private:
    void UpdateHUD();
    void EndGame();

    // used to control the repeating timer & to store the remaining time in seconds
   
    FTimerHandle CountdownHandle;
    float TimeRemaining; // in seconds

    // allows selecting a UMG Widget blueprint to display the timer

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> TimerWidgetClass; 

    // stores the instance of the timer widget at runtime & a reference to the text block inside the widget so it can be updated

    UUserWidget* TimerWidgetInstance;
    UTextBlock* TimerTextBlock;
};
