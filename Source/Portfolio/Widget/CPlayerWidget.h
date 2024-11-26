#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerWidget.generated.h"

class UProgressBar;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthChanged, float, NewHealth); // Todo. UI랑 연동해보기.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStaminaChanged, float, NewStamina);

UCLASS()
class PORTFOLIO_API UCPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void UpdateHealthBar(float Health);
	void UpdateStaminaBar(float Stamina);

	void OnHealthChanged(float NewHealth);
	void OnStaminaChanged(float NewStamina);

public:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* StaminaBar;

};
