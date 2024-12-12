#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

class UNiagaraComponent;
class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class PORTFOLIO_API ACProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UNiagaraComponent* ParticleComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UBoxComponent* BoxComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Component")
		UProjectileMovementComponent* ProjectileComp;
};
