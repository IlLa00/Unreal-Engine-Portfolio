#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Summon.generated.h"

class ACPetController;
class ACPet;

UCLASS()
class PORTFOLIO_API USummon : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

private:
	ACPetController* PetController;
	ACPet* Pet;
};
