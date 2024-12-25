#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CAttackCompInterface.generated.h"

class UBoxComponent;

UINTERFACE(MinimalAPI)
class UCAttackCompInterface : public UInterface
{
	GENERATED_BODY()
};

class PORTFOLIO_API ICAttackCompInterface
{
	GENERATED_BODY()

public:
	virtual UBoxComponent* GetAttackComp() = 0;
};
