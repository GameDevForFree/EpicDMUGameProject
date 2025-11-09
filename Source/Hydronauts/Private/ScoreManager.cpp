#include "ScoreManager.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

AScoreManager::AScoreManager()
{
    PrimaryActorTick.bCanEverTick = false;
    PlayerScore = 0;
    ScoreWidgetInstance = nullptr;
    ScoreTextBlock = nullptr;
}

void AScoreManager::AddScore(int32 Points)
{
    PlayerScore += Points;
    UpdateHUD();
}

void AScoreManager::UpdateHUD()
{
    if (!ScoreWidgetInstance && ScoreWidgetClass)
    {
        ScoreWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
        if (ScoreWidgetInstance)
            ScoreWidgetInstance->AddToViewport();

        // Find the TextBlock inside the widget
        ScoreTextBlock = Cast<UTextBlock>(ScoreWidgetInstance->GetWidgetFromName(TEXT("ScoreText")));
    }

    if (ScoreTextBlock)
    {
        ScoreTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), PlayerScore)));
    }
}
