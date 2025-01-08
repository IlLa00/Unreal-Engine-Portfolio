#include "CCharacterAttributeSet.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Widget/CPlayerWidget.h"

UCCharacterAttributeSet::UCCharacterAttributeSet()
{
	BaseHealth = 100.f;
	BaseStamina = 100.f;

	InitCurrentHealth(GetBaseHealth()); 
	InitCurrentStamina(GetBaseStamina());
}

void UCCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    if (Attribute == GetCurrentStaminaAttribute())  
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetBaseStamina() + 0.1f);
    }
    else if (Attribute == GetCurrentHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetBaseHealth() + 0.1f);
    }
}

void UCCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetCurrentStaminaAttribute()) 
    {
        if (GetCurrentStamina() == 0.f)
        {
            OnStaminaEmpty.Broadcast();
        }
        OnStaminaChanged.Broadcast(NewValue); 
    }

    if (Attribute == GetCurrentHealthAttribute())
    {
        if (NewValue <= 0.f)
        {
            ACPlayer* Player =  Cast<ACPlayer>(GetOwningActor());
            CheckNull(Player);

            Player->Death();
        }

       OnHealthChanged.Broadcast(NewValue); 
    }
}

void UCCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

}
