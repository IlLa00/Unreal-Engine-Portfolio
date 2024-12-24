#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HookGun.generated.h"

class UProjectileMovementComponent;
class UCableComponent;
class ACHookGun;
class ACPlayer;

UCLASS()
class PORTFOLIO_API UHookGun : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UHookGun();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

protected:
	void FireHook();
	void SplineLaunch(FVector HitLocation);

	void FireEnd();

private:
	UAnimMontage* AttackMontage;

	FTimerHandle TraceTimerHandle;
	FTimerHandle EndTimerHandle;
};
