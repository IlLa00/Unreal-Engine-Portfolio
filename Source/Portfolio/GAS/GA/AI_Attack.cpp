#include "AI_Attack.h"
#include "Global.h"
#include "GAS/GE/Damage.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"

void UAI_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// MontageToPlay에 원하는거 넣기
	// 이 함수는 캔슬 어빌리티가 호출되기까지 계속 발동됨
	ACPet* Pet = Cast<ACPet>(OwnerInfo->AvatarActor);
	if (Pet)
	{
		if (Pet->GetDataAsset())
		{
			MontageToPlay = Pet->GetDataAsset()->MontageDatas.AttackMontage[0];
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData); 

}
