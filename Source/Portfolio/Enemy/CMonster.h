#pragma once

#include "CoreMinimal.h"
#include "CEnemy.h"
#include "Interface/CAttackCompInterface.h"
#include "CMonster.generated.h"

class UBoxComponent;
class UWidgetComponent;
class UCEnemyHealthWidget;
class UCMonsterMeshDataAsset;

UCLASS()
class PORTFOLIO_API ACMonster : public ACEnemy, public ICAttackCompInterface
{
	GENERATED_BODY()
	
public:
	ACMonster();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:
	FORCEINLINE virtual UCMonsterMeshDataAsset* GetDataAsset() { return DataAsset; }
	FORCEINLINE virtual UCEnemyHealthWidget* GetHealthWidget() { return HealthWidgetObject; }
	FORCEINLINE virtual int32 GetIndex() { return Index; } // ÇÊ¿ä?

	virtual UBoxComponent* GetAttackComp() override { return AttackComp; }
	
public:
	void SetMesh(FName PlayerArea);
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* HealthWidgetComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UBoxComponent* AttackComp;

private:
	UCEnemyHealthWidget* HealthWidgetObject;
	UCMonsterMeshDataAsset* DataAsset;
	int32 Index;
};