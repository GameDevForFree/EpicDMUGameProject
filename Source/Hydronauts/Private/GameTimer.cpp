// // All code by Michael Threfall P2797637 with assistance from Alex Robertson P2607829

#include "GameTimer.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AGameTimer::AGameTimer()
{
    PrimaryActorTick.bCanEverTick = false; // disabled as we are using a timer, instead of per frame updates 
    TimeRemaining = 900.f; // sets the timer to start at 900 seconds (15 minutes)
    TimerWidgetInstance = nullptr; // initializes the widget pointer to null
    TimerTextBlock = nullptr; // initializes the reference to the text block to null
}

void AGameTimer::BeginPlay()
{
    Super::BeginPlay();

    
    // checks if there is a widget blueprint is assigned in the editor
    // then it instantiaties it. Afterwards adds it onto the screen as a HUD

    if (TimerWidgetClass)
    {
        TimerWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), TimerWidgetClass);
        if (TimerWidgetInstance)
        {
            TimerWidgetInstance->AddToViewport();

            
            TimerTextBlock = Cast<UTextBlock>(TimerWidgetInstance->GetWidgetFromName(TEXT("TimerText")));
        }
    }

    // timer settings, such as a repeating timer that calls UpdateHUD every one second, handle to control/stop the timer later, etc
    
    GetWorldTimerManager().SetTimer(CountdownHandle, this, &AGameTimer::UpdateHUD, 1.0f, true);
}

void AGameTimer::UpdateHUD()
{
    // checks if the timer has hit zero and if it has, to use the EndGame() function which boots the players back to the main menu

    if (TimeRemaining <= 0.f)
    {
        EndGame();
        return;
    }

    
    int Minutes = FMath::FloorToInt(TimeRemaining / 60); // calculates whole minutes
    int Seconds = FMath::FloorToInt(FMath::Fmod(TimeRemaining, 60)); // calculates remaining seconds
    FString TimerString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds); // formats the timer string

    // updates the UI with the current timer value

    if (TimerTextBlock)
    {
        TimerTextBlock->SetText(FText::FromString(TimerString));
    }

    TimeRemaining -= 1.f;
}

// stops the timer and boots the players to the main menu when this function is called

void AGameTimer::EndGame()
{
    GetWorldTimerManager().ClearTimer(CountdownHandle);

    
    UGameplayStatics::OpenLevel(this, FName("LVL_MainMenu"));
}
