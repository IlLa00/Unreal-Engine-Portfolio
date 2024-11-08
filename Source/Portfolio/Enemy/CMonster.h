#pragma once

#include "CoreMinimal.h"
#include "CEnemy.h"
#include "CMonster.generated.h"

UCLASS()
class PORTFOLIO_API ACMonster : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACMonster();

public:
	UPROPERTY(EditDefaultsOnly, Category = "MeshClass")
		TSubclassOf<USkeletalMesh> MeshAssets[8];
};
