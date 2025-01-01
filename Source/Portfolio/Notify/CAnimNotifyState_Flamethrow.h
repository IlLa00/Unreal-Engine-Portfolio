#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_Flamethrow.generated.h"


UCLASS()
class PORTFOLIO_API UCAnimNotifyState_Flamethrow : public UAnimNotifyState
{
	GENERATED_BODY()
	
private:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);

};
