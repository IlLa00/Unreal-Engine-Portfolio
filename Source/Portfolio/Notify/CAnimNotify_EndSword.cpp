#include "CAnimNotify_EndSword.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Equipment/CEquipment.h"
#include "Weapon/CSword.h"
#include "GAS/GA/Sword.h"

FString UCAnimNotify_EndSword::GetNotifyName() const
{
	return "EndSword";
}

void UCAnimNotify_EndSword::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(Player);

	if (!Player->GetEquipment()->GetCurrentCurrentEquipWeapon()) return;
	if (!Player->GetEquipment()->GetCurrentCurrentEquipWeapon()->IsA<ACSword>()) return;

	ACSword* Sword = Cast<ACSword>(Player->GetEquipment()->GetCurrentCurrentEquipWeapon());
	CheckNull(Sword);

	Sword->GetAbilitySystemComponent()->CancelAbilityHandle(Sword->GetAbilitySystemComponent()->FindAbilitySpecFromClass(USword::StaticClass())->Handle);
}
