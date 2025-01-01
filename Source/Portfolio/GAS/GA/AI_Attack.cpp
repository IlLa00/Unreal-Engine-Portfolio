#include "AI_Attack.h"
#include "Global.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"
#include "Enemy/CMonster.h"
#include "Enemy/CBoss.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "DataAsset/CBossDataAsset.h"
#include "CAnimInstance.h"

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
			CheckNull(Boss);

			UCAnimInstance* Anim = Cast<UCAnimInstance>(Boss->GetMesh()->GetAnimInstance());
			CheckNull(Anim);

			CheckNull(Boss->GetBossDataAsset());
			
			if(Anim->IsFly)
				MontageToPlay = Boss->GetBossDataAsset()->MontageDatas.AttackMontage[0];
			else
				MontageToPlay = Boss->GetBossDataAsset()->MontageDatas.AttackMontage[1]; // todo.. 나중에 수정해야할수도
		}
		else
		{
			ACMonster* Monster = Cast<ACMonster>(OwnerInfo->AvatarActor);
			if (Monster)
			{
				if (Monster->GetDataAsset())
				{
					MontageToPlay = Monster->GetDataAsset()->Datas[Monster->GetIndex()].MontageDatas.AttackMontage[0];
				}
			}
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData); 
}
