#include "CAnimNotify_EndReload.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "GAS/GA/ReloadRifle.h"
#include "AbilitySystemComponent.h"
#include "Equipment/CEquipment.h"
#include "Weapon/CRifle.h"

FString UCAnimNotify_EndReload::GetNotifyName() const
{
	return "EndReload";
}

void UCAnimNotify_EndReload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(Player);

	if (!Player->GetEquipment()->GetCurrentCurrentEquipWeapon()) return;
	if (!Player->GetEquipment()->GetCurrentCurrentEquipWeapon()->IsA<ACRifle>()) return;

	ACRifle* Rifle = Cast<ACRifle>(Player->GetEquipment()->GetCurrentCurrentEquipWeapon());
	CheckNull(Rifle);

	Rifle->SetReloadMode(false);

	Rifle->GetAbilitySystemComponent()->CancelAbilityHandle(Rifle->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UReloadRifle::StaticClass())->Handle);

}