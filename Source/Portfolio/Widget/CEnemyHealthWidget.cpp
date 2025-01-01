#include "CEnemyHealthWidget.h"
#include "Global.h"
#include "Components/ProgressBar.h"


void UCEnemyHealthWidget::Update(float NewHealth, float BaseHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(NewHealth / BaseHealth);
	}
}