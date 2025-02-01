#include "CInventory.h"
#include "Global.h"
#include "Widget/CInventoryWidget.h"
#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/CItem_Test.h"

UCInventory::UCInventory()
{
	CHelpers::GetClass(&WidgetClass, "/Game/Widget/BP_CInventoryWidget");
	CheckNull(WidgetClass);
}

void UCInventory::PostInitProperties()
{
	Super::PostInitProperties();

}

void UCInventory::OnOffInventoryWidget()
{
	CheckNull(WidgetClass);

	if (Widget)
		Widget = nullptr;

	if (!Widget)
	{
		Widget = CreateWidget<UCInventoryWidget>(Owner->GetWorld(), WidgetClass);
		CheckNull(Widget);

		Widget->AddToViewport();

		Owner->GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		Owner->GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}
}

void UCInventory::SetOwner(ACPlayer* InOwner)
{
	Owner = InOwner;
}

void UCInventory::AddItemToInventory(ACItem_Test* Item)
{
	CheckNull(Item);

	if (Item->GetItemName().IsValid() && !Item->GetItemName().ToString().IsEmpty())
	{
		if (Items.Contains(Item->GetItemName())) // 지랄 여기서 또 문제가 터진다고? 그냥 contain쓰지말자
		{
			(*Items.Find(Item->GetItemName()))->IncreaseCount();
		}
		else
		{
			Items.Emplace(Item->GetItemName(), Item);
		}
	}

}
