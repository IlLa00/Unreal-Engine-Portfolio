#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CMonsterMeshDataAsset.generated.h"

class UCAnimInstance;
class ACItem;

USTRUCT(BlueprintType)
struct FMontageData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UAnimMontage>> AttackMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HittedMontage;

};

USTRUCT(BlueprintType)
struct FMonsterData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TObjectPtr<USkeletalMesh> SkeletalMeshAssets; 

	UPROPERTY(EditAnywhere)
		TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditAnywhere)
		FMontageData MontageDatas;

	UPROPERTY(EditAnywhere)
		float BaseHealth;

	UPROPERTY(EditAnywhere)
		float BaseDamage;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ACItem>> DropItems;
};


UCLASS()
class PORTFOLIO_API UCMonsterMeshDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Monster Data")
		FMonsterData Datas[8];
	
};
