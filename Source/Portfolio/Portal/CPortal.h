#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPortal.generated.h"

UCLASS()
class PORTFOLIO_API ACPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPortal();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* MeshComp;

};
