#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Interface/CAIInterface.h"
#include "CEnemy.generated.h"

class UTextRenderComponent;
class UWidgetComponent;
class UAbilitySystemComponent;
class UBehaviorTree;
class UCAIAttributeSet;
class UCDamageWidget;

UCLASS()
class PORTFOLIO_API ACEnemy : public ACharacter, public IAbilitySystemInterface, public ICAIInterface
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
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual FGameplayTagContainer& GetTagContainer() override { return TagContainer; }
	virtual UCAIAttributeSet* GetAIAttributeSet() override { return AIAttribute; }
	virtual UWidgetComponent* GetDamageTextComponent() override { return DamageTextComp; }

	UBehaviorTree* GetBehaviorTree() { return BT; }

	UFUNCTION()
		void SetDamageText(float NewValue);

	void HiddenDamage();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Text")
		UTextRenderComponent* TextComp;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		UWidgetComponent* DamageTextComp;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC;
		
	UPROPERTY(EditDefaultsOnly, Category = "Behavior Tree")
		UBehaviorTree* BT; 

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		FGameplayTagContainer TagContainer;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UCAIAttributeSet> AIAttribute;
	
protected:
	TSubclassOf<UCDamageWidget> DamageWidgetClass;
};
