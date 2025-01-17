#include "GE_HookGun.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"

UGE_HookGun::UGE_HookGun()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo Modifier;
    Modifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(
        UCCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCCharacterAttributeSet, CurrentStamina)
    ));

    Modifier.ModifierOp = EGameplayModOp::Additive;
    Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(-50.f);

    Modifiers.Add(Modifier);
}
