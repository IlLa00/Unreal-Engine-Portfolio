#include "AI_GetHit.h"
#include "Global.h"
#include "Enemy/CMonster.h"
#include "Pet/CPet.h"
#include "DataAsset/CPetDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAI_GetHit::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (OwnerInfo->AvatarActor->IsA<ACMonster>())
	{
		ACMonster* Monster = Cast<ACMonster>(OwnerInfo->AvatarActor);
		CheckNull(Monster);
		CheckNull(Monster->GetDataAsset());

		Monster->GetCharacterMovement()->StopMovementImmediately();

		MontageToPlay = Monster->GetDataAsset()->Datas->MontageDatas.HittedMontage;
	}
	else if (OwnerInfo->AvatarActor->IsA<ACPet>())
	{
		ACPet* Pet = Cast<ACPet>(OwnerInfo->AvatarActor);
		CheckNull(Pet);
		CheckNull(Pet->GetDataAsset());

		MontageToPlay = Pet->GetDataAsset()->MontageDatas.HittedMontage;
	}

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
}
