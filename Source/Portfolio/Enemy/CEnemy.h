#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

class UTextRenderComponent;
class UAbilitySystemComponent;
class UBehaviorTree;
class UCMonsterMeshDataAsset;
class UCMonsterAttributeSet;

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
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UBehaviorTree* GetBehaviorTree() { return BT; }

	FORCEINLINE virtual FGameplayTagContainer& GetTagContainer() { return TagContainer; }
	FORCEINLINE virtual UCMonsterAttributeSet* GetAttributeSet() { return Attribute; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Text")
		UTextRenderComponent* TextComp;

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
};
