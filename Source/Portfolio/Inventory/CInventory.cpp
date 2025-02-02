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
	if (ItemDatas.IsEmpty())
		PrintLine(); // 대체 왜걸림?


	if (Row.Name.IsValid())
	{
		if (ItemDatas.Contains(Row.Name)) // 동일한 값이 있으면
		{
			int32* Count = ItemCount.Find(Row.Name);

			++(*Count); 

			CLog::Print(*Count);
			ItemCount.Emplace(Row.Name, *Count);
		}
		else // 동일한 값이 없으면 = 새로운 값이면
		{
			int32 Count = 1;

			ItemDatas.Emplace(Row.Name, Row);
			ItemCount.Emplace(Row.Name, Count);
		}
	}
}
