#include "Aim.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "GameFramework/SpringArmComponent.h"

UAim::UAim()
{
}

void UAim::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

	Player->GetSpringArmComp()->TargetArmLength = 100.f;

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAim::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

	Player->GetSpringArmComp()->TargetArmLength = 200.f;

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
