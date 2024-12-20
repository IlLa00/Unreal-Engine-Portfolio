#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Aim.generated.h"

UCLASS()
class PORTFOLIO_API UAim : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UAim();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

};
