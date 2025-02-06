#include "CWeaponAttributeSet.h"
#include "Global.h"
#include "Widget/CPlayerWidget.h"
#include "Player/CPlayer.h"


void UCWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

}

void UCWeaponAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == GetCurrentProficiencyAttribute())
	{
		ACPlayer* Player = Cast<ACPlayer>(GetOwningActor()->GetOwner());
		CheckNull(Player);

		Player->GetPlayerWidget()->UpdateEquipWeaponProficiency(NewValue);

		if (GetCurrentProficiency() >= GetBaseProficiency())
		{
			OnUpdateProficiency.Broadcast(NewValue);
			SetCurrentProficiency(0.f);

		}
	}
}
