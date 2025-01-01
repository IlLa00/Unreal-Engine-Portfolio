#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CEnemyHealthWidget.generated.h"

class UProgressBar;

UCLASS()
class PORTFOLIO_API UCEnemyHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void Update(float NewHealth, float BaseHealth);

private:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;
};
