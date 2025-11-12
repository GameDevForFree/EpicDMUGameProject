// All code here is by Alex Robertson P2607829

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

    // components/variables

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Points);

    UFUNCTION(BlueprintCallable, Category = "Score")
    void SubtractScore(int32 Points); // NEW

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ScoreWidgetClass;

private:
    int32 PlayerScore;

    UUserWidget* ScoreWidgetInstance;
    UTextBlock* ScoreTextBlock;

    void UpdateHUD();
};
