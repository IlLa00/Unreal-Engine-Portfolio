#include "CInventoryWidget.h"
#include "Global.h"
#include "Components/Button.h"
#include "Player/CPlayer.h"
#include "Inventory/CInventory.h"
#include "Item/CItem_Test.h"

void UCInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ACPlayer* Player = Cast<ACPlayer>(GetOwningPlayer()->GetPawn());
	CheckNull(Player);

	CheckNull(Player->GetInventory());

	for (const auto& Item : Player->GetInventory()->GetItems())
	{
		Button1->WidgetStyle.Normal.SetResourceObject(Item->GetItemTexture());
	}
}
