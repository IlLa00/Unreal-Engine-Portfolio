#include "CDeathWidget.h"
#include "Global.h"
#include "Components/Button.h"
#include "Player/CPlayer.h"
#include "GAS/Attribute/CCharacterAttributeSet.h"
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
	ACPlayer* Player = Cast<ACPlayer>(GetOwningPlayer()->GetPawn());
	CheckNull(Player);

	if (Player->GetMesh()->IsSimulatingPhysics())
	{
		Player->GetMesh()->SetSimulatePhysics(false);
	}

	if (!(Player->GetMesh()->GetCollisionProfileName() == FName("CharacterMesh")))
	{
		Player->GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
	}

	Player->GetMesh()->AttachToComponent(Player->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	Player->GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	Player->GetMesh()->UpdateComponentToWorld();

	Player->GetAttributeSet()->SetCurrentHealth(Player->GetAttributeSet()->GetBaseHealth());

	this->SetVisibility(ESlateVisibility::Hidden);
	
	ACPortal* Portal = Cast<ACPortal>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPortal::StaticClass()));
	CheckNull(Portal);

	Portal->ShowPortalWidget();
}
