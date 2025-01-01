#include "CBossWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"

void UCBossWidget::Update(float NewHealth, float BaseHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(NewHealth / BaseHealth);
	}

	if (CurrentHealthBox)
	{
		CurrentHealthBox->SetText(FText::AsNumber(NewHealth));
	}

	if (BaseHealthBox)
	{
		BaseHealthBox->SetText(FText::AsNumber(BaseHealth));
	}
}
