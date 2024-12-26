#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_Montage.h"

#include "AI_Dead.generated.h"

class ACharacter;

UCLASS()
class PORTFOLIO_API UAI_Dead : public UGameplayAbility_Montage
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	void Dead(ACharacter* Character);

private:
	FTimerHandle DeadTimer;
};
