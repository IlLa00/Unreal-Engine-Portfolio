#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerWidget.generated.h"

class UProgressBar;

UCLASS()
class PORTFOLIO_API UCPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnHealthChange(float NewHealth);

	UFUNCTION()
		void OnStaminaChange(float NewStamina);
	
	void UpdateHealthBar(float Health);
	void UpdateStaminaBar(float Stamina);


public:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* PlayerHealthBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* PlayerStaminaBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* PetHealthBar;

};
