#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CInventory.generated.h"

class UCInventoryWidget;
class ACPlayer;
class ACItem_Test;

UCLASS()
class PORTFOLIO_API UCInventory : public UObject
{
	GENERATED_BODY()
	
public:
	UCInventory();

public:
	virtual void PostInitProperties() override;

	FORCEINLINE TMap<FName, ACItem_Test*> GetItems() { return Items; }

	void OnOffInventoryWidget();
	void SetOwner(ACPlayer* InOwner);

	void AddItemToInventory(ACItem_Test* Item);

private:
	TMap<FName, ACItem_Test*> Items;

	TSubclassOf<UCInventoryWidget> WidgetClass;
	UCInventoryWidget* Widget;

	ACPlayer* Owner;
};
