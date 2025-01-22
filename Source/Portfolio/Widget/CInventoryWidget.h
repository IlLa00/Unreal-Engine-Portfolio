#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CInventoryWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class PORTFOLIO_API UCInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

	void CancelWidget();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* Button1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button1Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Buttons[36];

	int32 Index;

};
