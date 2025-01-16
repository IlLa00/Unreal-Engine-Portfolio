#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "TESTGameplayEffect.generated.h"


UCLASS()
class PORTFOLIO_API UTESTGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UTESTGameplayEffect();
	
public:
	void SetModifier(float Value);
};
