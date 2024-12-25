#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPortalWidget.generated.h"

class UButton;

UCLASS()
class PORTFOLIO_API UCPortalWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void TeleportToGrassland();

	UFUNCTION()
		void TeleportToRockPlain();

	UFUNCTION()
		void TeleportToDessert();

	UFUNCTION()
		void TeleportToBambooForest();

	UFUNCTION()
		void TeleportToCliff();

	UFUNCTION()
		void CancelWidget();

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* GrasslandButton;
	
	UPROPERTY(meta = (BindWidget))
		UButton* RockPlainButton;

	UPROPERTY(meta = (BindWidget))
		UButton* DessertButton;
			
	UPROPERTY(meta = (BindWidget))
		UButton* BambooForestButton;
		
	UPROPERTY(meta = (BindWidget))
		UButton* CliffButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CancelButton;
			
};
