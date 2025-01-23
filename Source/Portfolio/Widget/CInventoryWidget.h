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

	UFUNCTION()
		void CancelWidget();

private:
	TArray<UButton*> Buttons;
	TArray<UTextBlock*> Texts;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* Button1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button1Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button2Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button3;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button3Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button4;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button4Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button5;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button5Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button6;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button6Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button7;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button7Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button8;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button8Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button9;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button9Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button10;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button10Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button11;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button11Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button12;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button12Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button13;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button13Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button14;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button14Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button15;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button15Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button16;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button16Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button17;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button17Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button18;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button18Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button19;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button19Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button20;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button20Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button21;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button21Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button22;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button22Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button23;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button23Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button24;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button24Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button25;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button25Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button26;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button26Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button27;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button27Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button28;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button28Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button29;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button29Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button30;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button30Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button31;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button31Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button32;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button32Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button33;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button33Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button34;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button34Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button35;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button35Text;

	UPROPERTY(meta = (BindWidget))
	UButton* Button36;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Button36Text;


};
