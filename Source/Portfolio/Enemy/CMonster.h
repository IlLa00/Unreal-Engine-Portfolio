#pragma once

#include "CoreMinimal.h"
#include "CEnemy.h"
#include "CMonster.generated.h"

class UCMonsterMeshDataAsset;

UCLASS()
class PORTFOLIO_API ACMonster : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACMonster();

public:
	void SetMesh(FName PlayerArea);
	void SetAnimClass();

public:
	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
		UCMonsterMeshDataAsset* DataAsset;
};