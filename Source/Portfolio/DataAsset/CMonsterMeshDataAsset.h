#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CMonsterMeshDataAsset.generated.h"

class UCAnimInstance;

UCLASS()
class PORTFOLIO_API UCMonsterMeshDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "SkeletalMesh")
		TObjectPtr<USkeletalMesh> SkeletalMeshAssets[8];

	UPROPERTY(EditAnywhere, Category = "AnimClass")
		TSubclassOf<UAnimInstance> AnimClass[8];
	
};
