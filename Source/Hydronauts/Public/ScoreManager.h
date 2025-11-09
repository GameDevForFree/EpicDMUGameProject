#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "ScoreManager.generated.h"

class UTextBlock;

UCLASS()
class HYDRONAUTS_API AScoreManager : public AActor
{
    GENERATED_BODY()

public:
    AScoreManager();

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Points);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ScoreWidgetClass; // assign WBP_ScoreHUD in Editor

private:
    int32 PlayerScore;

    UUserWidget* ScoreWidgetInstance;
    UTextBlock* ScoreTextBlock;

    void UpdateHUD();
};
