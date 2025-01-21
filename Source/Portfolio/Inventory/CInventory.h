#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CInventory.generated.h"

class UCInventoryWidget;
class ACPlayer;
class ACItem;

UCLASS()
class PORTFOLIO_API UCInventory : public UObject
{
	GENERATED_BODY()
	
public:
	UCInventory();

public:
	virtual void PostInitProperties() override;

	void OnOffInventoryWidget();
	void SetOwner(ACPlayer* InOwner);

private:
	TArray<ACItem*> Items;

	TSubclassOf<UCInventoryWidget> WidgetClass;
	UCInventoryWidget* Widget;

	ACPlayer* Owner;
};
