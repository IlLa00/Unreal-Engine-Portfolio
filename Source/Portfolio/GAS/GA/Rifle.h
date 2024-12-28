#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Rifle.generated.h"

class ACPlayer;

UCLASS()
class PORTFOLIO_API URifle : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	URifle();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

private:
	void Shoot();

private:
	UAnimMontage* AttackMontage;
	FTimerHandle TimerHandle;
};

