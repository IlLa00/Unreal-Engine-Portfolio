#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCPlayerWidget;
class UAbilitySystemComponent;
class UCCharacterAttributeSet;
class UGameplayEffect;
class ACEquipment;

UCLASS()
class PORTFOLIO_API ACPlayer : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	void SetGAS();
	void SetGameplayAbility();
	void SetGameplayEffect();

	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void OnSummon();

	void OnEquipFirstSlot();
	void OnEquipSecondSlot();
	void OnEquipThirdSlot();
	void OnEquipLastSlot();

public:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	FORCEINLINE UCCharacterAttributeSet* GetAttributeSet() { return AttributeSet; } // 이렇게 가져와야하는건가싶음
	FORCEINLINE FGameplayTagContainer GetTagContainer() { return TagContainer; }
	FORCEINLINE UCPlayerWidget* GetPlayerWidget() { return PlayerWidget; }
	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }

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

	UPROPERTY(EditDefaultsOnly, Category = "GE")
		TSubclassOf<UGameplayEffect> BPRegenerateStaminaEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		TSubclassOf<ACEquipment> EquipmentClass;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
		int32 TeamId;

private:
	UCPlayerWidget* PlayerWidget;
	ACEquipment* Equipment;

	FGameplayTagContainer TagContainer;
	FGameplayEffectSpecHandle RegenerateStminaHandle;
};
