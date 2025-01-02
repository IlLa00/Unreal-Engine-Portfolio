#include "CPetWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"

void UCPetWidget::Update(float NewHealth, float BaseHealth)
{
	PetHealthBar->SetPercent(NewHealth / BaseHealth);
}