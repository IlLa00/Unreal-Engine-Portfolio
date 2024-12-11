#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_SpawnProjectile.generated.h"

class ACProjectile;

UCLASS()
class PORTFOLIO_API UCAnimNotify_SpawnProjectile : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UCAnimNotify_SpawnProjectile();

protected:
	FString GetNotifyName() const;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditDefaultsOnly,Category = "Projectile Class")
		TSubclassOf<ACProjectile> ProjectileClass;
};
