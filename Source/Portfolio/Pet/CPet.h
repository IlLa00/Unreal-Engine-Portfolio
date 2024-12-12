#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CPet.generated.h"

class UCapsuleComponent;
class UTextRenderComponent;
class UAbilitySystemComponent;
class UBehaviorTree;
class UCPetAttributeSet;
class UCPetDataAsset;

UCLASS()
class PORTFOLIO_API ACPet : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACPet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UBehaviorTree* GetBehaviorTree() { return BT; }

	FORCEINLINE virtual FGameplayTagContainer& GetTagContainer() { return TagContainer; }
	FORCEINLINE virtual UCPetDataAsset* GetDataAsset() { return DataAsset; }
	FORCEINLINE virtual UCPetAttributeSet* GetAttributeSet() { return Attribute; }

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditDefaultsOnly, Category = "Text")
		UTextRenderComponent* TextComp;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
		UBehaviorTree* BT;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		FGameplayTagContainer TagContainer;
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UCPetAttributeSet> Attribute;

protected:
	UCPetDataAsset* DataAsset;
};
