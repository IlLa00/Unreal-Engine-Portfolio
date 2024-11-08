#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPet.generated.h"

class UCapsuleComponent;

UCLASS()
class PORTFOLIO_API ACPet : public ACharacter
{
	GENERATED_BODY()

public:
	ACPet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

};
