#include "DataAsset/CWeaponDataAsset.h"
#include "Global.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"

UCWeaponDataAsset::UCWeaponDataAsset()
{
	for (const auto& data : Datas)
	{
		if (Cast<UCWeaponAttributeSet>(data.AttributeClass))
		{
			UCWeaponAttributeSet* WeaponAttributeSet = Cast<UCWeaponAttributeSet>(data.AttributeClass);
			WeaponAttributeSet->SetBaseDamage(data.BaseDamage);
			WeaponAttributeSet->SetBaseProficiency(data.BaseProficiency);
		}
			
	}
}
