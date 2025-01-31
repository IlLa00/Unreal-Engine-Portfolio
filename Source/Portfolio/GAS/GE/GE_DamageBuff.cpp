#include "GAS/GE/GE_DamageBuff.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"

UGE_DamageBuff::UGE_DamageBuff()
{
    DurationPolicy = EGameplayEffectDurationType::HasDuration;

    FScalableFloat DurationValue;
    DurationValue.SetValue(10.0f);

    DurationMagnitude = DurationValue;

    FGameplayModifierInfo Modifier;
    Modifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(
        UCWeaponAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCWeaponAttributeSet, CurrentDamage)
    ));

    Modifier.ModifierOp = EGameplayModOp::Additive;
    Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(10.f);

    Modifiers.Add(Modifier);
}
