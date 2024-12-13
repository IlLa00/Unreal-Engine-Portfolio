#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility_Montage.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "AI_GetHit.generated.h"

UCLASS()
class PORTFOLIO_API UAI_GetHit : public UGameplayAbility_Montage
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
