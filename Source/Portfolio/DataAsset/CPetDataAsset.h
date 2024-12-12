#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CPetDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FMontageDatas
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UAnimMontage>> AttackMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HittedMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DeadMontage;
};

UCLASS()
class PORTFOLIO_API UCPetDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Montage Data")
		FMontageDatas MontageDatas;

	UPROPERTY(EditAnywhere, Category = "Attribute")
		float BaseHealth;

	UPROPERTY(EditAnywhere, Category = "Attribute")
		float BaseDamage;
};
