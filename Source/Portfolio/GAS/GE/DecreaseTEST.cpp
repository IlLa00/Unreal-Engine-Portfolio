#include "GAS/GE/DecreaseTEST.h"

UDecreaseTEST::UDecreaseTEST()
{
    // 지속 시간 정책 (Duration Policy)
    DurationPolicy = EGameplayEffectDurationType::Instant;

    // Modifier 설정
    FGameplayModifierInfo ModifierInfo;
    ModifierInfo.Attribute = UCharacterAttributeSet::GetCurrentStaminaAttribute();
    ModifierInfo.ModifierOp = EGameplayModOp::Additive;
    ModifierInfo.Magnitude.SetMagnitude(EScalableFloatMagnitudeType::ScalableFloat, -5.0f); // 스태미나 감소량
    Modifiers.Add(ModifierInfo);

    // 발동 확률 (Chance to Apply to Target)
    ChanceToApplyToTarget.SetValue(1.0f); // 100% 적용

    // 주기적 억제 정책 (Periodic Inhibition Policy)
    PeriodicInhibitionPolicy = EGameplayEffectPeriodInhibitionPolicy::NeverReset;

    // 디스플레이 옵션 (Display Options)
    bRequireModifierSuccessToTriggerCues = true;
    bSuppressStackingCues = false;
}