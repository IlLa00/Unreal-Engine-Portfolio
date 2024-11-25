#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCPlayerWidget;
class UAbilitySystemComponent;
class UCCharacterAttributeSet;


UCLASS()
class PORTFOLIO_API ACPlayer : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void OnSummon();
	
public:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<UCPlayerWidget> WidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UCCharacterAttributeSet> AttributeSet; // 있어야 어트리뷰트 가져올 수 잇음, 에디터에선 어디서 확인?

private:
	UCPlayerWidget* PlayerWidget;

	FGameplayTagContainer TagContatiner;
};
