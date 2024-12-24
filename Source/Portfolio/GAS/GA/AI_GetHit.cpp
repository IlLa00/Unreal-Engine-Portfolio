#include "AI_GetHit.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"

void UAI_GetHit::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACEnemy* Enemy = Cast<ACEnemy>(OwnerInfo->AvatarActor);
	if (Enemy)
	{
		if (Enemy->GetDataAsset())
		{
			MontageToPlay = Enemy->GetDataAsset()->Datas->MontageDatas.HittedMontage;
			PrintLine();
		}
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData); 

}
