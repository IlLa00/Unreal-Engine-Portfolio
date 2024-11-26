#include "CPlayerWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

void UCPlayerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 위젯에서 캐릭터의 AbilitySystemComponent에 연결
    ACPlayer* Player = Cast<ACPlayer>(GetOwningPlayerPawn());
    if(Player)
    {
        if (Player && Player->GetAbilitySystemComponent())
        {
            // 체력과 스테미나 값이 변경될 때마다 호출되는 콜백을 설정
            UpdateHealthBar(Player->GetAttributeSet()->GetCurrentHealth());
            UpdateStaminaBar(Player->GetAttributeSet()->GetCurrentStamina());
        }
    }
}

void UCPlayerWidget::UpdateHealthBar(float Health)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(Health / 100.f);  // 0 ~ 100 사이로 비율 계산
    }
}

void UCPlayerWidget::UpdateStaminaBar(float Stamina)
{
    if (StaminaBar)
    {
        StaminaBar->SetPercent(Stamina / 100.f);  // 0 ~ 100 사이로 비율 계산
    }
}

void UCPlayerWidget::OnHealthChanged(float NewHealth)
{
    UpdateHealthBar(NewHealth);
}

void UCPlayerWidget::OnStaminaChanged(float NewStamina)
{
    UpdateStaminaBar(NewStamina);
}
