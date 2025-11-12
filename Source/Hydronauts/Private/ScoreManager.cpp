// All code here is by Alex Robertson P2607829

#include "ScoreManager.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

AScoreManager::AScoreManager()
{
    // initializes score and widget pointers to safe defaults

    PrimaryActorTick.bCanEverTick = false; // disabled as the score doesn’t need per-frame updates
    PlayerScore = 0;
    ScoreWidgetInstance = nullptr;
    ScoreTextBlock = nullptr;
}

// adds the given number of points to the score, afterwards calls UpdateHUD() to refresh the display

void AScoreManager::AddScore(int32 Points)
{
    PlayerScore += Points;
    UpdateHUD();
}

// subtracts points but clamps the result so the score never drops below 0, afterwards updates the HUD again

void AScoreManager::SubtractScore(int32 Points)
{
    
    PlayerScore = FMath::Max(PlayerScore - Points, 0);
    UpdateHUD();
}

// ensures a widget exists before updating

void AScoreManager::UpdateHUD()
{
    if (!ScoreWidgetInstance && ScoreWidgetClass)
    {
        ScoreWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
        if (ScoreWidgetInstance)
            ScoreWidgetInstance->AddToViewport();

       
        ScoreTextBlock = Cast<UTextBlock>(ScoreWidgetInstance->GetWidgetFromName(TEXT("ScoreText")));
    }

    if (ScoreTextBlock)
    {
        ScoreTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), PlayerScore)));
    }
}
