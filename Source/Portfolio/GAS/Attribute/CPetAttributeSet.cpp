#include "GAS/Attribute/CPetAttributeSet.h"

UCPetAttributeSet::UCPetAttributeSet()
{
	BaseHealth = 100.f;
	BaseAttack = 10.f;

	InitCurrentHealth(GetBaseHealth()); // current와 base값을 같게함
	InitCurrentAttack(GetBaseAttack());
}

void UCPetAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UCPetAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
}

void UCPetAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
