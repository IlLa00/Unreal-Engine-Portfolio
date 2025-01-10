#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPG.generated.h"

UCLASS()
class PORTFOLIO_API URPG : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	URPG();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

private:
	TSubclassOf<AActor> Rocket;
};
