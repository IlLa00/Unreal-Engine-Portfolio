#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class PORTFOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Movement")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Movement")
		float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "GameplayTag")
		FGameplayTagContainer TagContainer;
};
