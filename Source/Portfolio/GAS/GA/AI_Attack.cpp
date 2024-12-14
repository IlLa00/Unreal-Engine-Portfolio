#include "AI_Attack.h"
#include "Global.h"
#include "GAS/GE/Damage.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"
#include "Enemy/CEnemy.h"
#include "DataAsset/CMonsterMeshDataAsset.h"

void UAI_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// 이 함수는 캔슬 어빌리티가 호출되기까지 계속 발동됨
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
		ACEnemy* Enemy = Cast<ACEnemy>(OwnerInfo->AvatarActor);
		if (Enemy)
		{
			if (Enemy->GetDataAsset())
			{	
				MontageToPlay = Enemy->GetDataAsset()->Datas[Enemy->GetIndex()].MontageDatas.AttackMontage[0]; // 이거 공격추가되면 그거 되게 해야할지도?
			}
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData); 
}
