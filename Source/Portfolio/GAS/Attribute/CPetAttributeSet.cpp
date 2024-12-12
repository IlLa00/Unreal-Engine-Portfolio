#include "GAS/Attribute/CPetAttributeSet.h"

UCPetAttributeSet::UCPetAttributeSet()
{

}

void UCPetAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UCPetAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetCurrentHealthAttribute()) // 스테미나가 변경된거면
    {
        OnHealthChanged.Broadcast(NewValue); // UI연동
    }
}

void UCPetAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
