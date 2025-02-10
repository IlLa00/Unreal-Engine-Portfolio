#include "CInventory.h"
#include "Global.h"
#include "Widget/CInventoryWidget.h"
#include "Player/CPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataTable/CItemDataTable.h"

UCInventory::UCInventory()
{
	CHelpers::GetClass(&WidgetClass, "/Game/Widget/BP_CInventoryWidget");
	CheckNull(WidgetClass);
}

void UCInventory::PostInitProperties()
{
	Super::PostInitProperties();

	AddToRoot();

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

void UCInventory::AddItemToInventory(const FItemDataTable Row)
{
	if (Row.Name.IsValid())
	{
		if (ItemDatas.Contains(Row.Name)) 
		{
			int32* Count = ItemCount.Find(Row.Name);

			++(*Count); 

			ItemCount.Emplace(Row.Name, *Count);
		}
		else 
		{
			int32 Count = 1;

			ItemDatas.Emplace(Row.Name, Row);
			ItemCount.Emplace(Row.Name, Count);
		}
	}
}
void UCInventory::AddItemToInventory(const FItemDataTable Row)
{
	if (Row.Name.IsValid())
	{
		if (ItemDatas.Contains(Row.Name)) 
		{
			int32* Count = ItemCount.Find(Row.Name);

			++(*Count); 

			ItemCount.Emplace(Row.Name, *Count);
		}
		else 
		{
			int32 Count = 1;

			ItemDatas.Emplace(Row.Name, Row);
			ItemCount.Emplace(Row.Name, Count);
		}
	}
}