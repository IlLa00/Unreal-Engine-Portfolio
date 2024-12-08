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

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void SetMesh(FName PlayerArea);

public:
	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
		UCMonsterMeshDataAsset* DataAsset;
};