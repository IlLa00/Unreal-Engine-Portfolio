#include "CDamageWidget.h"
#include "Global.h"
#include "Components/EditableTextBox.h"
#include "Interface/CAIInterface.h"
#include "GAS/Attribute/CAIAttributeSet.h"

void UCDamageWidget::SetDamageText(float NewValue)
{
	DamageText->SetText(FText::AsNumber(NewValue));

	ShowDamageText();
}
