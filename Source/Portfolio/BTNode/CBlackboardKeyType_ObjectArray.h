#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "CBlackboardKeyType_ObjectArray.generated.h"

UCLASS()
class PORTFOLIO_API UCBlackboardKeyType_ObjectArray : public UBlackboardKeyType
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackboardKey")
        TArray<UObject*> Objects;
};
