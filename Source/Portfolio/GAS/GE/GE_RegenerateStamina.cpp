#include "GAS/GE/GE_RegenerateStamina.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

UGE_RegenerateStamina::UGE_RegenerateStamina()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo Modifier;
    Modifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(
        UCCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCCharacterAttributeSet, CurrentStamina)
    ));

    Modifier.ModifierOp = EGameplayModOp::Additive;
    Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(0.5f);

    Modifiers.Add(Modifier);
}