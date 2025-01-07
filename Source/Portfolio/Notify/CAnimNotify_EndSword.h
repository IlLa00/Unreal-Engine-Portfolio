#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndSword.generated.h"

UCLASS()
class PORTFOLIO_API UCAnimNotify_EndSword : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	FString GetNotifyName() const;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
