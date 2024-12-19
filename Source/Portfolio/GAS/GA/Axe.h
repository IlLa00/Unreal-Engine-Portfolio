#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Axe.generated.h"

UCLASS()
class PORTFOLIO_API UAxe : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UAxe();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

private:
	UAnimMontage* AttackMontage;
};
