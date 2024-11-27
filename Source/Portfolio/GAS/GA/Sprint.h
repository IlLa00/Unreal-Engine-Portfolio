#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Sprint.generated.h"

UCLASS()
class PORTFOLIO_API USprint : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	USprint();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

private:
	void DecreaseStamina();

public:
	UPROPERTY(EditDefaultsOnly, Category = "GE")
		TSubclassOf<UGameplayEffect> BPMovementEffect;

private:
	FTimerHandle DecreaseStaminaTimerHandle;
	
};
