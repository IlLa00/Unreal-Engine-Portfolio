#include "GAS/Attribute/CCharacterAttributeSet.h"

UCCharacterAttributeSet::UCCharacterAttributeSet()
{
	BaseHealth = 100.f;
	BaseStamina = 100.f;

	InitCurrentHealth(GetBaseHealth()); // current와 base값을 같게함
	InitCurrentStamina(GetBaseStamina());

}

void UCCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

}

void UCCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{

}

void UCCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    //Super::PostGameplayEffectExecute(Data);

    //// 스테미나와 체력 값이 변경되었을 때 UI를 업데이트할 수 있도록 알림
    //if (Data.EvaluatedData.Attribute == GetBaseHealth())
    //{
    //    // Health 값이 변경되었을 때 호출
    //    // 예: UI 업데이트
    //}
    //else if (Data.EvaluatedData.Attribute == GetBaseStamina())
    //{
    //    // Stamina 값이 변경되었을 때 호출
    //    // 예: UI 업데이트
    //}
}
