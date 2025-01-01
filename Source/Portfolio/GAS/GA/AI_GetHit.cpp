#include "AI_GetHit.h"
#include "Global.h"
#include "Enemy/CMonster.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"

void UAI_GetHit::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACMonster* Monster = Cast<ACMonster>(OwnerInfo->AvatarActor);
	if (Monster)
	{
		if (Monster->GetDataAsset())
		{
			MontageToPlay = Monster->GetDataAsset()->Datas->MontageDatas.HittedMontage;
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData); 
}
