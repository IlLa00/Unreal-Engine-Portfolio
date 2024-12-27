#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Sword.generated.h"

UCLASS()
class PORTFOLIO_API USword : public UGameplayAbility
{
	GENERATED_BODY()

public:
	USword();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	
private:
	UAnimMontage* AttackMontageClasses[4];
	int32 ComboCount;

	TSubclassOf<UGameplayEffect> BPDecreaseStaminaEffect;
};
