#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CRifle.generated.h"

UCLASS()
class PORTFOLIO_API ACRifle : public ACWeapon
{
	GENERATED_BODY()
	
public:	
	ACRifle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		void Shooting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Reloading();


	bool IsReload() { return bReload; }
	void SetReloadMode(bool state) { bReload = state; }

public:
	void Reload();

protected:
	UPROPERTY(EditDefaultsOnly)
		int32 bullet;

private:
	bool bReload;
};
