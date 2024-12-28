#include "ReloadRifle.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "GameFramework/Character.h"
#include "Weapon/CRifle.h"

UReloadRifle::UReloadRifle()
{
	CHelpers::GetAsset(&ReloadMontage, "/Game/Assets/Montage/Reload_Rifle_Hip_Montage");
	CheckNull(ReloadMontage);

}

void UReloadRifle::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACharacter* Character = Cast<ACharacter>(OwnerInfo->AvatarActor->GetOwner());
	CheckNull(Character);

	Character->PlayAnimMontage(ReloadMontage);

	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
}

void UReloadRifle::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	ACRifle* Rifle = Cast<ACRifle>(ActorInfo->AvatarActor);
	CheckNull(Rifle);

	Rifle->Reload(); // 30¹ß ÃæÀü

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

