#include "CAnimNotify_Equip.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Equipment/CEquipment.h"

FString UCAnimNotify_Equip::GetNotifyName() const
{
	return "Equip";
}

void UCAnimNotify_Equip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(Player);

	Player->GetEquipment()->Begin_Equip();
}
