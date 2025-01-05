#include "CDeathWidget.h"
#include "Global.h"
#include "Components/Button.h"
#include "Portal/CPortal.h"
#include "GameFramework/Character.h"

bool UCDeathWidget::Initialize()
{
	bool bSuccess = Super::Initialize();

	if (!ReviveButton) return false;
	ReviveButton->OnClicked.AddDynamic(this, &UCDeathWidget::Revive);

	return true;
}

void UCDeathWidget::Revive()
{
	PrintLine();

	this->SetVisibility(ESlateVisibility::Hidden);

	GetOwningPlayer()->GetCharacter()->GetMesh()->SetSimulatePhysics(false);
	GetOwningPlayer()->GetCharacter()->GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	ACPortal* Portal = Cast<ACPortal>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPortal::StaticClass()));
	CheckNull(Portal);

	Portal->ShowPortalWidget();
}
