#include "Sword.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"

USword::USword()
{
	CHelpers::GetAsset(&AttackMontageClasses[0], "/Game/Assets/Montage/Frank_RPG_Warrior_Combo01_1_Montage");
	CHelpers::GetAsset(&AttackMontageClasses[1], "/Game/Assets/Montage/Frank_RPG_Warrior_Combo01_2_Montage");
	CHelpers::GetAsset(&AttackMontageClasses[2], "/Game/Assets/Montage/Frank_RPG_Warrior_Combo01_3_Montage");
	CHelpers::GetAsset(&AttackMontageClasses[3], "/Game/Assets/Montage/Frank_RPG_Warrior_Combo01_4_Montage");

	CHelpers::GetClass(&BPDecreaseStaminaEffect, "/Game/GAS/BP_GE_DecreaseStamina");
	CheckNull(BPDecreaseStaminaEffect);
}

void USword::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

	if (Player->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("Character.State.StaminaEmpty"))))
	{
		return;
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (Player->GetCurrentMontage() == AttackMontageClasses[0])
	{
		Player->StopAnimMontage();
		Player->PlayAnimMontage(AttackMontageClasses[1]);
	}
	else if (Player->GetCurrentMontage() == AttackMontageClasses[1])
	{
		Player->StopAnimMontage();
		Player->PlayAnimMontage(AttackMontageClasses[2]);
	}
	else if (Player->GetCurrentMontage() == AttackMontageClasses[2])
	{
		Player->StopAnimMontage();
		Player->PlayAnimMontage(AttackMontageClasses[3]);
	}
	else
		Player->PlayAnimMontage(AttackMontageClasses[0]);

	CheckNull(BPDecreaseStaminaEffect);

	FGameplayEffectContextHandle EffectContext = Player->GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpecHandle = Player->GetAbilitySystemComponent()->MakeOutgoingSpec(BPDecreaseStaminaEffect, 1.0f, EffectContext);
	
	Player->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), Player->GetAbilitySystemComponent());
}

void USword::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
