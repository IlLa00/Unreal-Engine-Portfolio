#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CBossDataAsset.generated.h"

class ACItem;

USTRUCT(BlueprintType)
struct FBossMontageDatas
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UAnimMontage>> AttackMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HittedMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> TakeOffMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> LandMontage;
};

UCLASS()
class PORTFOLIO_API UCBossDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Montage Data")
	FBossMontageDatas MontageDatas;

	UPROPERTY(EditAnywhere, Category = "Attribute")
	float BaseHealth;

	UPROPERTY(EditAnywhere, Category = "Attribute")
	float BaseDamage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACItem> DropItem;
	
};
