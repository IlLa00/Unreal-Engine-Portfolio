#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CDeathWidget.generated.h"

class UButton;

UCLASS()
class PORTFOLIO_API UCDeathWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

public:
	UFUNCTION()
		void Revive();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* ReviveButton;
};
