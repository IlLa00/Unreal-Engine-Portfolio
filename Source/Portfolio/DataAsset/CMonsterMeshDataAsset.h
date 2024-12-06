#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CMonsterMeshDataAsset.generated.h"

class UCAnimInstance;

USTRUCT(BlueprintType)
struct FMontageData
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

USTRUCT(BlueprintType)
struct FEquipmentData
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
		AActor* DropEmitter;
};


UCLASS()
class PORTFOLIO_API UCMonsterMeshDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Monster Data")
		FEquipmentData Datas[8];
	
};
