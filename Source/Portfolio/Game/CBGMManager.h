#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBGMManager.generated.h"

class UCBGMDataAsset;
class UAudioComponent;

UCLASS()
class PORTFOLIO_API ACBGMManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBGMManager();

protected:
	virtual void BeginPlay() override;

public:
	void SetBGM(FName Area);

protected:
	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* AudioComp;

private:
	UCBGMDataAsset* DataAsset;
};
