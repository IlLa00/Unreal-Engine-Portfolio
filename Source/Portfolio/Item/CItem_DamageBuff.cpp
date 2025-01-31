#include "Item/CItem_DamageBuff.h"
#include "Global.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Player/CPlayer.h"
#include "Equipment/CEquipment.h"
#include "Weapon/CWeapon.h"
#include "DataAsset/CItemDataAsset.h"
#include "GAS/Attribute/CWeaponAttributeSet.h"

ACItem_DamageBuff::ACItem_DamageBuff()
{
	CHelpers::CreateSceneComponent(this, &NiagaraComp, "NiagaraComp", RootGravityComp);
	CheckNull(NiagaraComp);

	CHelpers::GetClass(&BPDamageBuffEffect, "/Game/GAS/BP_GE_DamageBuff");
	CheckNull(BPDamageBuffEffect);
}

void ACItem_DamageBuff::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Data : DataAsset->Datas)
	{
		if (GetClass() == Data.Item)
		{
			Value = Data.Value;
			break;
		}
	}
}

void ACItem_DamageBuff::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	CheckNull(Player);

	// Player->OnBuff();

	ACWeapon** Weapons = Player->GetEquipment()->GetEquipWeapons();
	CheckNull(Weapons);
	
	for (int i = 0; i < 4; i++)
	{
		PrintLine();
		(*Weapons[i]).OnDamageBuff();
	}

	Destroy();
}
