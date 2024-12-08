#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_CheckGameplayTagsOnActor.h"
#include "CBTDecorator_CheckGameplayTags.generated.h"

UCLASS()
class PORTFOLIO_API UCBTDecorator_CheckGameplayTags : public UBTDecorator_CheckGameplayTagsOnActor
{
	GENERATED_BODY()

public:
	UCBTDecorator_CheckGameplayTags();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
