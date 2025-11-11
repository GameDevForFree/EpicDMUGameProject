#include "GameTimer.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AGameTimer::AGameTimer()
{
    PrimaryActorTick.bCanEverTick = false;
    TimeRemaining = 1500.f; // 25 minutes in seconds
    TimerWidgetInstance = nullptr;
    TimerTextBlock = nullptr;
}

void AGameTimer::BeginPlay()
{
    Super::BeginPlay();

    // Spawn the HUD widget
    if (TimerWidgetClass)
    {
        TimerWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), TimerWidgetClass);
        if (TimerWidgetInstance)
        {
            TimerWidgetInstance->AddToViewport();

            // Find the TextBlock inside the widget
            TimerTextBlock = Cast<UTextBlock>(TimerWidgetInstance->GetWidgetFromName(TEXT("TimerText")));
        }
    }

    // Start ticking every second
    GetWorldTimerManager().SetTimer(CountdownHandle, this, &AGameTimer::UpdateHUD, 1.0f, true);
}

void AGameTimer::UpdateHUD()
{
    if (TimeRemaining <= 0.f)
    {
        EndGame();
        return;
    }

    // Format MM:SS
    int Minutes = FMath::FloorToInt(TimeRemaining / 60);
    int Seconds = FMath::FloorToInt(FMath::Fmod(TimeRemaining, 60));
    FString TimerString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

    if (TimerTextBlock)
    {
        TimerTextBlock->SetText(FText::FromString(TimerString));
    }

    TimeRemaining -= 1.f;
}

void AGameTimer::EndGame()
{
    GetWorldTimerManager().ClearTimer(CountdownHandle);

    // Replace with your end level
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}
