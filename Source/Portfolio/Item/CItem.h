#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CItem.generated.h"

UCLASS()
class PORTFOLIO_API ACItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
