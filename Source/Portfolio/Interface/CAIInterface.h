#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CAIInterface.generated.h"

class UCAIAttributeSet;

UINTERFACE(MinimalAPI)
class UCAIInterface : public UInterface
{
	GENERATED_BODY()
};

class PORTFOLIO_API ICAIInterface
{
	GENERATED_BODY()

public:
	virtual FGameplayTagContainer& GetTagContainer() = 0;
	virtual UCAIAttributeSet* GetAIAttributeSet() = 0;
	
};
