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
class UTextRenderComponent;
class UCPlayerWidget;
class UCDeathWidget;
class UAbilitySystemComponent;
class UCCharacterAttributeSet;
class UGameplayEffect;
class ACEquipment;
class UNiagaraComponent;
class UNiagaraSystem;
class UCInventory;

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

	void Death();

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

	void OnMainAction();
	void OffMainAction();

	void OnSubAction();
	void OffSubAction();

	void OnReload();

	void OnJump();
	void OffJump();

	void ShowDeathWidget();

	void OnOffInventory();

public:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void OnStaminaEmpty();

	FORCEINLINE UCCharacterAttributeSet* GetAttributeSet() { return AttributeSet; } 
	FORCEINLINE FGameplayTagContainer& GetTagContainer() { return TagContainer; }
	FORCEINLINE UCPlayerWidget* GetPlayerWidget() { return PlayerWidget; }
	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE USpringArmComponent* GetSpringArmComp() { return SpringArmComp; }
	FORCEINLINE UCameraComponent* GetCameraComp() { return CameraComp; }
	FORCEINLINE UCInventory* GetInventory() { return Inventory; }

	void SetUsePawnControlRotation(bool bUse);
	void CanDoAbilities();

	void OnBuff();
	void OffBuff();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Niagara")
		UNiagaraComponent* NiagaraComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UTextRenderComponent* TextComp;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<UCPlayerWidget> WidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<UCDeathWidget> DeathWidgetClass;
		
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		TObjectPtr<UCCharacterAttributeSet> AttributeSet; 

	UPROPERTY(EditDefaultsOnly, Category = "GE")
		TSubclassOf<UGameplayEffect> BPRegenerateStaminaEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
		TSubclassOf<ACEquipment> EquipmentClass;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
		int32 TeamId;

	UPROPERTY(EditDefaultsOnly, Category = "Niagara")
		UNiagaraSystem* OverlapParitcle;

private:
	UCPlayerWidget* PlayerWidget;
	UCDeathWidget* DeathWidget;
	ACEquipment* Equipment;

	FGameplayTagContainer TagContainer;
	FGameplayEffectSpecHandle RegenerateStminaHandle;

	FTimerHandle WidgetHandle;

	UCInventory* Inventory;
};
