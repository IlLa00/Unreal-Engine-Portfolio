#include "CCharacterAttributeSet.h"
#include "Global.h"
#include "Widget/CPlayerWidget.h"

UCCharacterAttributeSet::UCCharacterAttributeSet()
{
	BaseHealth = 100.f;
	BaseStamina = 100.f;

	InitCurrentHealth(GetBaseHealth()); // current와 base값을 같게함
	InitCurrentStamina(GetBaseStamina());

}

void UCCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    // PreAttributeChange는 속성 변경이 실제로 발생하기 전에 자동으로 호출됩니다. 따라서 속성 값을 검증하거나 변경하기에 적합한 시점입니다.
    if (Attribute == GetCurrentStaminaAttribute())  
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetBaseStamina() + 0.1f);
    }
}

void UCCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    // **PostAttributeChange**는 속성 값이 변경된 후 호출되는 함수로, 그 변경에 대한 후속 작업이나 상태 처리를 할 수 있는 중요한 위치입니다.

    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetCurrentStaminaAttribute()) // 스테미나가 변경된거면
    {
        OnStaminaChanged.Broadcast(NewValue); // UI연동
    }

    if (Attribute == GetCurrentHealthAttribute())
    {
        if (OldValue > NewValue)
        {
           OnHealthChanged.Broadcast(NewValue); // UI연동
        }
    }
}

void UCCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    //PostGameplayEffectExecute는 Gameplay Effect가 적용된 후에 호출되는 함수로, 그 결과에 따른 후속 작업을 처리하는 데 사용됩니다. 예를 들어, 속성 값이 변경된 후 UI를 갱신하거나, 특정 조건을 만족할 경우 이벤트를 트리거하는 등의 작업을 처리할 수 있습니다.
}
