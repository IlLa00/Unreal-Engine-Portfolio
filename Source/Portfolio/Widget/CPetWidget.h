#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPetWidget.generated.h"

class UProgressBar;

UCLASS()
class PORTFOLIO_API UCPetWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Update(float NewHealth, float BaseHealth);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* PetHealthBar;

};
