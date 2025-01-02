#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Interface/CAIInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CPet.generated.h"

class UCapsuleComponent;
class UTextRenderComponent;
class UAbilitySystemComponent;
class UBehaviorTree;
class UCAIAttributeSet;
class UCPetDataAsset;
class UCPetWidget;

UCLASS()
class PORTFOLIO_API ACPet : public ACharacter, public IAbilitySystemInterface, public ICAIInterface
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
	virtual FGameplayTagContainer& GetTagContainer() override { return TagContainer; }
	virtual UCAIAttributeSet* GetAIAttributeSet() override { return AIAttribute; }
	UBehaviorTree* GetBehaviorTree() { return BT; }

	FORCEINLINE virtual UCPetDataAsset* GetDataAsset() { return DataAsset; }
	FORCEINLINE UCPetWidget* GetHealthWidget() { return PetWidget; }

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
		TObjectPtr<UCAIAttributeSet> AIAttribute;

protected:
	UCPetDataAsset* DataAsset;
	TSubclassOf<UCPetWidget> PetWidgetClass;
	UCPetWidget* PetWidget;
};
