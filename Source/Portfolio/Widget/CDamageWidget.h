#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CDamageWidget.generated.h"

class UEditableTextBox;

UCLASS()
class PORTFOLIO_API UCDamageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDamageText(float NewValue);

private:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* DamageText;
};
