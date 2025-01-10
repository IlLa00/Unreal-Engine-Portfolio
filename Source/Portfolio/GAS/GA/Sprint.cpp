#include "Sprint.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

USprint::USprint()
{
	CHelpers::GetClass(&BPMovementEffect, "/Game/GAS/BP_GE_Movement");
	CheckNull(BPMovementEffect);
}

void USprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor);
	CheckNull(Player);

	if (Player->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("Character.State.StaminaEmpty"))))
	{
		return;
	}

	Player->GetCharacterMovement()->MaxWalkSpeed = 600.f;

	GetWorld()->GetTimerManager().SetTimer(DecreaseStaminaTimerHandle, this, &USprint::DecreaseStamina, 0.1f, true, 0.1f);

	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	CheckNull(ASC);

	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(BPMovementEffect, 1.0f, EffectContext);

	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());


	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USprint::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor);
	CheckNull(Player);

	Player->GetCharacterMovement()->MaxWalkSpeed = 400.f;

	GetWorld()->GetTimerManager().ClearTimer(DecreaseStaminaTimerHandle);

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void USprint::DecreaseStamina()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();

	if (ASC)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(BPMovementEffect, 1.0f, EffectContext);

		ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

