#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CBoss.generated.h"

class UFloatingPawnMovement;
class UCBossDataAsset;
class UCBossWidget;

UCLASS()
class PORTFOLIO_API ACBoss : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACBoss();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE UFloatingPawnMovement* GetFloatingComp() { return FloatingComp; }
	FORCEINLINE UCBossDataAsset* GetBossDataAsset() { return BossDataAsset; }
	FORCEINLINE UCBossWidget* GetHealthWidget() { return BossWidget; }

public:
	void SetWidget(bool state);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AnimClass")
		TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UFloatingPawnMovement* FloatingComp;

private:
	UCBossDataAsset* BossDataAsset;
	TSubclassOf<UCBossWidget> BossWidgetClass;
	UCBossWidget* BossWidget;
};
