#include "GAS/Attribute/CCharacterAttributeSet.h"

UCCharacterAttributeSet::UCCharacterAttributeSet()
{
	BaseHealth = 100.f;
	BaseStamina = 100.f;

	InitBaseHealth(GetBaseHealth()); // current와 base값을 같게함
	InitBaseStamina(GetBaseStamina());

}

void UCCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

}

void UCCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{

}
