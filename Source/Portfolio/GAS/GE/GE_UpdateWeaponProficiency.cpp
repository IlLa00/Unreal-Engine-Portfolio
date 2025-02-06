#include "GAS/GE/GE_UpdateWeaponProficiency.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"

UGE_UpdateWeaponProficiency::UGE_UpdateWeaponProficiency()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo Modifier1;
    Modifier1.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(
        UCWeaponAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCWeaponAttributeSet, BaseDamage)
    ));

    Modifier1.ModifierOp = EGameplayModOp::Additive;
    Modifier1.ModifierMagnitude = FGameplayEffectModifierMagnitude(5.f);

    Modifiers.Add(Modifier1);

    FGameplayModifierInfo Modifier2;
    Modifier2.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(
        UCWeaponAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCWeaponAttributeSet, CurrentDamage)
    ));

    Modifier2.ModifierOp = EGameplayModOp::Additive;
    Modifier2.ModifierMagnitude = FGameplayEffectModifierMagnitude(5.f);

    Modifiers.Add(Modifier2);
}
