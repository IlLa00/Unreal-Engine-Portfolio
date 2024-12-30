#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawner.generated.h"

class ACMonster;
class ACBoss;
class ACEnemyController;

UCLASS()
class PORTFOLIO_API ACSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void Spawn(FVector PlayerLocation, FName PlayerArea);

	FVector SetSpawnRange(FVector PlayerLocation);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		int32 Number;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		TSubclassOf<ACMonster> MonsterClass;
};
