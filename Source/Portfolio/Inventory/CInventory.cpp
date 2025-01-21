#include "CInventory.h"
#include "Global.h"
#include "Widget/CInventoryWidget.h"
#include "Player/CPlayer.h"

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
	{
		Widget->RemoveFromParent();
		Widget = nullptr;
	}
	else
	{
		Widget = CreateWidget<UCInventoryWidget>(Owner->GetWorld(), WidgetClass);
		CheckNull(Widget);
		PrintLine();
		Widget->AddToViewport();
	}
}

void UCInventory::SetOwner(ACPlayer* InOwner)
{
	Owner = InOwner;
}
