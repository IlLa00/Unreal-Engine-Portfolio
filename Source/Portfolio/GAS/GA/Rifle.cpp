#include "GAS/GA/Rifle.h"
#include "Global.h"
#include "Player/CPlayer.h"

URifle::URifle()
{
	CHelpers::GetAsset(&AttackMontage, "/Game/Assets/Montage/Fire_Rifle_Ironsights_Montage");
	CheckNull(AttackMontage);
}

void URifle::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACPlayer* Player = Cast<ACPlayer>(ActorInfo->AvatarActor->GetOwner());
	CheckNull(Player);

	// GetWorld()->GetTimerManager().SetTimer()

	Player->PlayAnimMontage(AttackMontage);
	// 총쏘는 몽타주
	// 라인트레이스
	// 파티클 <- 근데 이건 큐 아님?
}

void URifle::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{

}
