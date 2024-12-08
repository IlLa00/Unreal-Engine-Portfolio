#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "GameplayTagContainer.h"
#include "CBTDecorator_TagCheck.generated.h"

UCLASS()
class PORTFOLIO_API UCBTDecorator_TagCheck : public UBTDecorator
{
	GENERATED_BODY()

public:
	UCBTDecorator_TagCheck();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, Category = GameplayTagCheck)
		FGameplayTag GameplayTag;
	
};
