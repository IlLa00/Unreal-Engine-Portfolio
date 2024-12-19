#include "Axe.h"
#include "Global.h"
#include "Player/CPlayer.h"

UAxe::UAxe()
{
	CHelpers::GetAsset(&AttackMontage, "/Game/Assets/Montage/Frank_RPG_Warrior_Combo01_1_Montage");
}

void UAxe::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

	Player->PlayAnimMontage(AttackMontage);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAxe::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{

}
