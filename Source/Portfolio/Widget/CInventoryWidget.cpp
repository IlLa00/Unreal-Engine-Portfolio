#include "CInventoryWidget.h"
#include "Global.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Player/CPlayer.h"
#include "Inventory/CInventory.h"
#include "Item/CItem_Test.h"

bool UCInventoryWidget::Initialize()
{
	bool Result = Super::Initialize();

	if (QuitButton)
		QuitButton->OnClicked.AddDynamic(this, &UCInventoryWidget::CancelWidget);

	return true;
}

void UCInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ACPlayer* Player = Cast<ACPlayer>(GetOwningPlayer()->GetPawn());
	CheckNull(Player);

	CheckNull(Player->GetInventory());

	Index = Player->GetInventory()->GetItems().Num();

	for (const auto& Item : Player->GetInventory()->GetItems())
	{
		Button1->WidgetStyle.Normal.SetResourceObject(Item.Value->GetItemTexture());
		Button1->WidgetStyle.Hovered.SetResourceObject(Item.Value->GetItemTexture());
		Button1->WidgetStyle.Pressed.SetResourceObject(Item.Value->GetItemTexture());

		Button1Text->SetText(FText::AsNumber(Item.Value->GetCount()));
	}

}

void UCInventoryWidget::CancelWidget()
{
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	RemoveFromParent();
}
