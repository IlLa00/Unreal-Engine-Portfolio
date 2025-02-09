#include "Aim.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Widget/CPlayerWidget.h"
#include "GameFramework/SpringArmComponent.h"

UAim::UAim()
{
}

void UAim::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

	Player->GetTagContainer().AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Sub.Aim")));

	Player->GetSpringArmComp()->TargetArmLength = 100.f;

	if(Player->GetPlayerWidget())
		Player->GetPlayerWidget()->SetAimWidget(true);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAim::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

	Player->GetTagContainer().RemoveTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Sub.Aim")));

	Player->GetSpringArmComp()->TargetArmLength = 200.f;

	if (Player->GetPlayerWidget())
		Player->GetPlayerWidget()->SetAimWidget(false);

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
