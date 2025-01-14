#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerWidget.generated.h"

class UProgressBar;
class UEditableTextBox;
class UImage;

UCLASS()
class PORTFOLIO_API UCPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnHealthChange(float NewHealth);

	UFUNCTION()
	void OnStaminaChange(float NewStamina);

	void UpdateHealthBar(float Health);
	void UpdateStaminaBar(float Stamina);

	void UpdateHealthText(float Health);
	void UpdateStaminaText(float Stamina);

	void UpdateEquipWeaponName(FText WeaponName);
	void UpdateEquipWeaponImage(UTexture* WeaponImage);
	void UpdateEquipWeaponProficiency(float Proficiency);

	void UpdateCurrentBullet(float Value);
	void UpdateBaseBullet(float Value);

	void ShowCurrentBullet(bool state);

	void SetAimWidget(bool state);

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* PlayerHealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PlayerStaminaBar;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CurrentHealthText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* BaseHealthText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CurrentStaminaText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* BaseStaminaText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EquipWeaponName;

	UPROPERTY(meta = (BindWidget))
	UImage* EquipWeaponImage;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProficiencyBar;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CurrentBullet;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* BaseBullet;

	UPROPERTY(meta = (BindWidget))
	UImage* AimImage;

};
