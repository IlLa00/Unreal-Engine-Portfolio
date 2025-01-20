#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CInventory.generated.h"

class ACItem;

UCLASS()
class PORTFOLIO_API UCInventory : public UObject
{
	GENERATED_BODY()
	
public:
	UCInventory();

public:
	virtual void PostInitProperties() override;

private:
	TArray<ACItem*> Items;
};
