#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRocket.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class PORTFOLIO_API ACRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRocket();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UProjectileMovementComponent* ProjectileComp;
};
