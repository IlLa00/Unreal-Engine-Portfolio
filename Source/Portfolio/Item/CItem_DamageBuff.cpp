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
	if (OverlapParitcle)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), OverlapParitcle, OtherActor->GetActorLocation());

	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	CheckNull(Player);

	ACWeapon** Weapons = Player->GetEquipment()->GetEquipWeapons();
	CheckNull(Weapons);
	
	for (int i = 0; i < 4; i++)
	{
		(*Weapons[i]).GetAttiribute()->SetBaseDamage((*Weapons[i]).GetAttiribute()->GetBaseDamage() + Value);
		(*Weapons[i]).GetAttiribute()->SetCurrentDamage((*Weapons[i]).GetAttiribute()->GetCurrentDamage() + Value);

		CLog::Print((*Weapons[i]).GetAttiribute()->GetBaseDamage());
		CLog::Print((*Weapons[i]).GetAttiribute()->GetCurrentDamage());
	}

	Destroy();
}
