#include "Axe.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "AbilitySystemComponent.h"

UAxe::UAxe()
{
	CHelpers::GetAsset(&AttackMontage, "/Game/Assets/Montage/Frank_RPG_Warrior_Combo01_1_Montage");

	CHelpers::GetClass(&BPDecreaseStaminaEffect, "/Game/GAS/BP_GE_DecreaseStamina");
	CheckNull(BPDecreaseStaminaEffect);
}

void UAxe::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

	Player->PlayAnimMontage(AttackMontage);

	if (Player->GetAbilitySystemComponent())
	{
		FGameplayEffectSpecHandle DecreaseStaminaHandle;
		FGameplayEffectContextHandle EffectContext = Player->GetAbilitySystemComponent()->MakeEffectContext();

		DecreaseStaminaHandle = Player->GetAbilitySystemComponent()->MakeOutgoingSpec(BPDecreaseStaminaEffect, 1.0f, EffectContext);

		Player->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*DecreaseStaminaHandle.Data.Get());
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAxe::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{

}
