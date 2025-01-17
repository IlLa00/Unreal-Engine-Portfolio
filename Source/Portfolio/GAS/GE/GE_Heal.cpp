#include "GE_Heal.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

UGE_Heal::UGE_Heal()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo Modifier;
    Modifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(
        UCCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCCharacterAttributeSet, CurrentHealth)
    ));

    Modifier.ModifierOp = EGameplayModOp::Additive;
    Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(10.f);

    Modifiers.Add(Modifier);
}
