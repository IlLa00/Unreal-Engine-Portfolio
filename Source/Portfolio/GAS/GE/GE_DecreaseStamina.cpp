#include "GE_DecreaseStamina.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

UGE_DecreaseStamina::UGE_DecreaseStamina()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo Modifier;
    Modifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(
        UCCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCCharacterAttributeSet, CurrentStamina)
    ));

    Modifier.ModifierOp = EGameplayModOp::Additive;  
    Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(-5.f); 

    Modifiers.Add(Modifier);
}
