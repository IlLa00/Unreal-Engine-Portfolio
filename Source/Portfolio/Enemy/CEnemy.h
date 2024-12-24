#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

class UTextRenderComponent;
class UWidgetComponent;
class UAbilitySystemComponent;
class UBehaviorTree;
class UCMonsterMeshDataAsset;
class UCMonsterAttributeSet;
class UCEnemyHealthWidget;
class UBoxComponent;

UCLASS()
class PORTFOLIO_API ACEnemy : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UBehaviorTree* GetBehaviorTree() { return BT; }

	FORCEINLINE virtual UCEnemyHealthWidget* GetHealthWidget() { return HealthWidgetObject; }
	FORCEINLINE virtual FGameplayTagContainer& GetTagContainer() { return TagContainer; }
	FORCEINLINE virtual UCMonsterAttributeSet* GetAttributeSet() { return Attribute; }
	FORCEINLINE virtual UCMonsterMeshDataAsset* GetDataAsset() { return DataAsset; }
	FORCEINLINE virtual UBoxComponent* GetAttackComp() { return AttackComp; }
	FORCEINLINE virtual int32 GetIndex() { return Index; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Text")
		UTextRenderComponent* TextComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UWidgetComponent* HealthWidgetComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UBoxComponent* AttackComp;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC;
		
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
		UBehaviorTree* BT; 

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		FGameplayTagContainer TagContainer;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UCMonsterAttributeSet> Attribute;

protected:
	UCMonsterMeshDataAsset* DataAsset;
	int32 Index;

public:
	UCEnemyHealthWidget* HealthWidgetObject;
};
