#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CInventoryWidget.generated.h"

class UButton;

UCLASS()
class PORTFOLIO_API UCInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// virtual bool Initialize() override;

	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button1;

};
