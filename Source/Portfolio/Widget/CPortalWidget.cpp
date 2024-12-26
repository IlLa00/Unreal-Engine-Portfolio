#include "CPortalWidget.h"
#include "Global.h"
#include "Components/Button.h"
#include "CGameModeBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UCPortalWidget::Initialize()
{
	bool bSuccess = Super::Initialize();

	if (!GrasslandButton) return false;
	GrasslandButton->OnClicked.AddDynamic(this, &UCPortalWidget::TeleportToGrassland);

	if (!RockPlainButton)  return false;
	RockPlainButton->OnClicked.AddDynamic(this, &UCPortalWidget::TeleportToRockPlain);

	if (!DessertButton)  return false;
	DessertButton->OnClicked.AddDynamic(this, &UCPortalWidget::TeleportToDessert);

	if (!BambooForestButton)  return false;
	BambooForestButton->OnClicked.AddDynamic(this, &UCPortalWidget::TeleportToBambooForest);

	if (!CliffButton)  return false;
	CliffButton->OnClicked.AddDynamic(this, &UCPortalWidget::TeleportToCliff);

	if (!CancelButton)  return false;
	CancelButton->OnClicked.AddDynamic(this, &UCPortalWidget::CancelWidget);

	return true;
}

void UCPortalWidget::TeleportToGrassland()
{
	ACGameModeBase* GameMode = Cast<ACGameModeBase>(GetWorld()->GetAuthGameMode());
	CheckNull(GameMode);

	GameMode->Teleport("Glassland");

	CancelWidget();
}

void UCPortalWidget::TeleportToRockPlain()
{
	ACGameModeBase* GameMode = Cast<ACGameModeBase>(GetWorld()->GetAuthGameMode());
	CheckNull(GameMode);

	GameMode->Teleport("RockPlain");

	CancelWidget();
}

void UCPortalWidget::TeleportToDessert()
{
	ACGameModeBase* GameMode = Cast<ACGameModeBase>(GetWorld()->GetAuthGameMode());
	CheckNull(GameMode);

	GameMode->Teleport("Dessert");

	CancelWidget();
}

void UCPortalWidget::TeleportToBambooForest()
{
	ACGameModeBase* GameMode = Cast<ACGameModeBase>(GetWorld()->GetAuthGameMode());
	CheckNull(GameMode);

	GameMode->Teleport("BambooForest");

	CancelWidget();
}

void UCPortalWidget::TeleportToCliff()
{
	ACGameModeBase* GameMode = Cast<ACGameModeBase>(GetWorld()->GetAuthGameMode());
	CheckNull(GameMode);

	GameMode->Teleport("Cliff");

	CancelWidget();
}

void UCPortalWidget::CancelWidget()
{
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());

	ACharacter* Character = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	CheckNull(Character);

	Character->GetCharacterMovement()->SetActive(true);

	SetVisibility(ESlateVisibility::Hidden);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
}

