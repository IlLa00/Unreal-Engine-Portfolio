#include "Sprint.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

USprint::USprint()
{
	CHelpers::GetClass(&BPMovementEffect, "/Game/GAS/BP_GE_Movement");
	CheckNull(BPMovementEffect);
}

void USprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor);

	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = 600.f;

		GetWorld()->GetTimerManager().SetTimer(DecreaseStaminaTimerHandle, this, &USprint::DecreaseStamina, 0.05f, true);
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USprint::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor);

	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = 400.f;

		GetWorld()->GetTimerManager().ClearTimer(DecreaseStaminaTimerHandle);
	}

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void USprint::DecreaseStamina()
{
	// 스테미너 감소 로직
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	PrintLine();
	if (ASC)
	{
		FGameplayEffectSpecHandle MovementHandle;
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();

		MovementHandle = ASC->MakeOutgoingSpec(BPMovementEffect, 1.0f, EffectContext);

		ASC->ApplyGameplayEffectSpecToSelf(*MovementHandle.Data.Get());
	}
}