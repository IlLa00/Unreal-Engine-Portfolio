#include "CDeathWidget.h"
#include "Global.h"
#include "Components/Button.h"
#include "Portal/CPortal.h"

bool UCDeathWidget::Initialize()
{
	bool bSuccess = Super::Initialize();

	if (!ReviveButton) return false;
	ReviveButton->OnClicked.AddDynamic(this, &UCDeathWidget::Revive);

	return true;
}

void UCDeathWidget::Revive()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	
	ACPortal* Portal = Cast<ACPortal>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPortal::StaticClass()));
	CheckNull(Portal);

	Portal->ShowPortalWidget();
}
