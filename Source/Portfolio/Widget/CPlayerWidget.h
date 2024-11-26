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

	// AbilitySystemComponent와 AttributeSet을 바인딩하기 위한 함수
	void UpdateHealthBar(float Health);
	void UpdateStaminaBar(float Stamina);

	// 스테미나와 체력 값 변경 시 호출될 함수
	void OnHealthChanged(float NewHealth);
	void OnStaminaChanged(float NewStamina);
public:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* StaminaBar;

};
