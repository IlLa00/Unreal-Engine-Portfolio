#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CBossWidget.generated.h"

class UProgressBar;
class UEditableTextBox;

UCLASS()
class PORTFOLIO_API UCBossWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Update(float NewHealth, float BaseHealth);

private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CurrentHealthBox;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* BaseHealthBox;
};
