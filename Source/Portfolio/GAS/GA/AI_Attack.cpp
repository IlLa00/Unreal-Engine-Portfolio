#include "AI_Attack.h"
#include "Global.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"
#include "Enemy/CEnemy.h"
#include "Enemy/CBoss.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "DataAsset/CBossDataAsset.h"

void UAI_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (OwnerInfo->AvatarActor->IsA<ACPet>())
	{
		ACPet* Pet = Cast<ACPet>(OwnerInfo->AvatarActor);
		if (Pet)
		{
			if (Pet->GetDataAsset())
			{
				MontageToPlay = Pet->GetDataAsset()->MontageDatas.AttackMontage[0];
			}
		}
	}
	else if (OwnerInfo->AvatarActor->IsA<ACEnemy>())
	{
		if (OwnerInfo->AvatarActor->IsA<ACBoss>())
		{
			ACBoss* Boss = Cast<ACBoss>(OwnerInfo->AvatarActor);
			if (Boss)
			{
				if (Boss->GetDataAsset())
				{
					MontageToPlay = Boss->GetDataAsset()->Datas->MontageDatas.AttackMontage[0]; // todo.. 배열처리 해야할지도
				}
			}
		}
		else
		{
			ACEnemy* Enemy = Cast<ACEnemy>(OwnerInfo->AvatarActor);
			if (Enemy)
			{
				if (Enemy->GetDataAsset())
				{
					MontageToPlay = Enemy->GetDataAsset()->Datas[Enemy->GetIndex()].MontageDatas.AttackMontage[0];
				}
			}
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData); 
}
