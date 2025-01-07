#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CBGMDataAsset.generated.h"

class USoundBase;

USTRUCT(BlueprintType)
struct FBGMDatas
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> BGM;

	UPROPERTY(EditAnywhere)
	FName BGMName;
};


UCLASS()
class PORTFOLIO_API UCBGMDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TArray<FBGMDatas> Datas;
};
