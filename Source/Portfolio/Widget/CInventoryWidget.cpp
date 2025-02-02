#include "CInventoryWidget.h"
#include "Global.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Player/CPlayer.h"
#include "Inventory/CInventory.h"
#include "Item/CItem.h"
#include "DataTable/CItemDataTable.h"

bool UCInventoryWidget::Initialize()
{
	bool Result = Super::Initialize();

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UCInventoryWidget::CancelWidget);
	}

	Buttons = { Button1 ,Button2,Button3,Button4,Button5,Button6,Button7,Button8,Button9,Button10,Button11,Button12,Button13,Button14,Button15,Button16,Button17,Button18,Button19,Button20,Button21,Button22,Button23,Button24,Button25,Button26,Button27,Button28,Button29,Button30,Button31,Button32,Button33,Button34,Button35,Button36 };

	Texts = { Button1Text ,Button2Text,Button3Text,Button4Text,Button5Text,Button6Text,Button7Text,Button8Text,Button9Text,Button10Text,Button11Text,Button12Text,Button13Text,Button14Text,Button15Text,Button16Text,Button17Text,Button18Text,Button19Text,Button20Text,Button21Text,Button22Text,Button23Text,Button24Text,Button25Text,Button26Text,Button27Text,Button28Text,Button29Text,Button30Text,Button31Text,Button32Text,Button33Text,Button34Text,Button35Text,Button36Text };

	return true;
}

void UCInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ACPlayer* Player = Cast<ACPlayer>(GetOwningPlayer()->GetPawn());
	CheckNull(Player);
	CheckNull(Player->GetInventory());

	int32 Index = 0;

	for (auto& Button : Buttons)
	{
		Button->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(0, 0, 0, 0.3));
	}

	for (const auto& ItemData : Player->GetInventory()->GetItemDatas())
	{
		Buttons[Index]->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(1, 1, 1, 1));

		Buttons[Index]->WidgetStyle.Normal.SetResourceObject(ItemData.Value.Texture);
		Buttons[Index]->WidgetStyle.Hovered.SetResourceObject(ItemData.Value.Texture);
		Buttons[Index]->WidgetStyle.Pressed.SetResourceObject(ItemData.Value.Texture);

		for (const auto& ItemCount : Player->GetInventory()->GetItemCount())
		{
			if (ItemCount.Key == ItemData.Key)
			{
				Texts[Index]->SetText(FText::AsNumber(ItemCount.Value));

				break;
			}
		}

		Index++;
	}
}

void UCInventoryWidget::CancelWidget()
{
	CheckNull(GetWorld());
	CheckNull(GetWorld()->GetFirstPlayerController());

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	RemoveFromParent();
}
