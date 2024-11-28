#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "CPetBTService_BBBase.generated.h"

UCLASS()
class PORTFOLIO_API UCPetBTService_BBBase : public UBTService_BlackboardBase
{
	GENERATED_BODY()

private:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
};
