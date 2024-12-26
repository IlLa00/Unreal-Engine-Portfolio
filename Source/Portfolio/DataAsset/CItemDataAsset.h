#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CItemDataAsset.generated.h"

class ACItem;

USTRUCT(BlueprintType)
struct FItemDatas
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACItem> Item;

	UPROPERTY(EditAnywhere)
		float Value;
};

UCLASS()
class PORTFOLIO_API UCItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TArray<FItemDatas> Datas;
};
