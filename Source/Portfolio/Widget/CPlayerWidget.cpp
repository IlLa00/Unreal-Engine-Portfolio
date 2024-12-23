#include "CPlayerWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
#include "Pet/CPet.h"
#include "GAS/Attribute/CPetAttributeSet.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"

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

    if (Player->GetAttributeSet())
    {
        Player->GetAttributeSet()->OnHealthChanged.AddDynamic(this, &UCPlayerWidget::OnHealthChange);
        Player->GetAttributeSet()->OnStaminaChanged.AddDynamic(this, &UCPlayerWidget::OnStaminaChange);
    }

    ACPet* Pet = nullptr;

    TArray<AActor*> Actors;
    Player->GetAttachedActors(Actors);

    if (Actors.Num() > 0)
    {
        for (const auto& Actor : Actors)
        {
            if (Actor->IsA<ACPet>())
            {
                Pet = Cast<ACPet>(Actor);
                break;
            }
        }
    }

    if (Pet)
    {
        if (Pet && Pet->GetAbilitySystemComponent())
        {
            // 체력과 스테미나 값이 변경될 때마다 호출되는 콜백을 설정
            UpdateHealthBar(Pet->GetAttributeSet()->GetCurrentHealth());
        }
        if (Pet->GetAttributeSet())
        {
            Pet->GetAttributeSet()->OnHealthChanged.AddDynamic(this, &UCPlayerWidget::OnHealthChange);
        }
    }

}

void UCPlayerWidget::UpdateHealthBar(float Health)
{
    if (PlayerHealthBar)
    {
        PlayerHealthBar->SetPercent(Health / 100.f);  // 0 ~ 100 사이로 비율 계산
    }
}

void UCPlayerWidget::UpdateStaminaBar(float Stamina)
{
    if (PlayerStaminaBar)
    {
        PlayerStaminaBar->SetPercent(Stamina / 100.f);  // 0 ~ 100 사이로 비율 계산
    }
}

void UCPlayerWidget::UpdateEquipWeaponName(FText WeaponName)
{
    EquipWeaponName->SetText(WeaponName);
}

void UCPlayerWidget::UpdateEquipWeaponImage(UTexture* WeaponImage)
{
    EquipWeaponImage->Brush.SetResourceObject(WeaponImage);
}

void UCPlayerWidget::OnHealthChange(float NewHealth)
{
    UpdateHealthBar(NewHealth);
}

void UCPlayerWidget::OnStaminaChange(float NewStamina)
{
    UpdateStaminaBar(NewStamina);
}
