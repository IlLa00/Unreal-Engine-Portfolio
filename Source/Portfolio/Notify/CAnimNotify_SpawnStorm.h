#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_SpawnStorm.generated.h"

class ACStorm;

UCLASS()
class PORTFOLIO_API UCAnimNotify_SpawnStorm : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UCAnimNotify_SpawnStorm();

protected:
	FString GetNotifyName() const;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Class")
		TSubclassOf<ACStorm> StormClass;
};
