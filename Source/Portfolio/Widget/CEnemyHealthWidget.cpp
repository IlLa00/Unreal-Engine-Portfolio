#include "CEnemyHealthWidget.h"
#include "Components/ProgressBar.h"

void UCEnemyHealthWidget::Update(float InCurrentHealth, float InMaxHealth)
{
	if (HealthBar)
		HealthBar->SetPercent(InCurrentHealth / InMaxHealth);
}