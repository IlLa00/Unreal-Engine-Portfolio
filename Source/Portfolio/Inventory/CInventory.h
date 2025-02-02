#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../DataTable/CItemDataTable.h"
#include "CInventory.generated.h"

class UCInventoryWidget;
class ACPlayer;

UCLASS()
class PORTFOLIO_API UCInventory : public UObject
{
	GENERATED_BODY()
	
public:
	UCInventory();

public:
	virtual void PostInitProperties() override;

	FORCEINLINE TMap<FName, FItemDataTable> GetItemDatas() { return ItemDatas; }
	FORCEINLINE TMap<FName, int32> GetItemCount() { return ItemCount; }

	void OnOffInventoryWidget();
	void SetOwner(ACPlayer* InOwner);

	void AddItemToInventory(const FItemDataTable Row);

private:
	UPROPERTY()
		TMap<FName, FItemDataTable> ItemDatas;

	UPROPERTY()
		TMap<FName, int32> ItemCount;

	TSubclassOf<UCInventoryWidget> WidgetClass;
	UCInventoryWidget* Widget;

	ACPlayer* Owner;
};
