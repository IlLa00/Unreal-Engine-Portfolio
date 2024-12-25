#include "CPortalWidget.h"
#include "Global.h"
#include "Components/Button.h"
#include "CGameModeBase.h"

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

	GameMode->Teleport();
}

void UCPortalWidget::TeleportToRockPlain()
{
}

void UCPortalWidget::TeleportToDessert()
{
}

void UCPortalWidget::TeleportToBambooForest()
{
}

void UCPortalWidget::TeleportToCliff()
{
}

void UCPortalWidget::CancelWidget()
{

}

