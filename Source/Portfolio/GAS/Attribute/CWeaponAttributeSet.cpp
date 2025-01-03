#include "CWeaponAttributeSet.h"
#include "Global.h"

UCWeaponAttributeSet::UCWeaponAttributeSet()
{
	
}

void UCWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

}

void UCWeaponAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == GetCurrentProficiencyAttribute())
	{
		if (GetCurrentProficiency() >= GetBaseProficiency())
		{
			SetBaseDamage(GetBaseDamage() + 5.f);
			SetCurrentDamage(GetBaseDamage());

			SetCurrentProficiency(0.f);

			CLog::Print(GetCurrentDamage());
		}
	}
}

void UCWeaponAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

}
