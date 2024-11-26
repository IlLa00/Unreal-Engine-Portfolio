#include "Sprint.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void USprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor);

	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
}

void USprint::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor);

	if (Character)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = 400.f;
	}
}
