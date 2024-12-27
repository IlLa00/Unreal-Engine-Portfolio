#include "ReloadRifle.h"
#include "Global.h"
#include "Player/CPlayer.h"

UReloadRifle::UReloadRifle()
{
	CHelpers::GetAsset(&ReloadMontage, "/Game/Assets/Montage/Reload_Rifle_Hip_Montage");
	CheckNull(ReloadMontage);

}

void UReloadRifle::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	MontageToPlay = ReloadMontage;

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
}

void UReloadRifle::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor);
	CheckNull(Player);


	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}
