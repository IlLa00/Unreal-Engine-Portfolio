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
	{
		Owner->GetCharacterMovement()->Activate();

		Widget->RemoveFromParent();
		Widget = nullptr;

		// Owner->GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
		Owner->GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		Owner->GetCharacterMovement()->Deactivate();

		Widget = CreateWidget<UCInventoryWidget>(Owner->GetWorld(), WidgetClass);
		CheckNull(Widget);

		Widget->AddToViewport();

		// Owner->GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		Owner->GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	}
}

void UCInventory::SetOwner(ACPlayer* InOwner)
{
	Owner = InOwner;
}

void UCInventory::AddItemToInventory(ACItem_Test* Item)
{
	Items.Add(Item);
	
}
