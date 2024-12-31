#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStorm.generated.h"

class UParticleSystemComponent;
class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class PORTFOLIO_API ACStorm : public AActor
{
	GENERATED_BODY()
	
public:
	ACStorm();

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
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UProjectileMovementComponent* ProjectileComp;

};
