#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRocket.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSphereTrace, FVector, Location);

UCLASS()
class PORTFOLIO_API ACRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRocket();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void Hit(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UProjectileMovementComponent* ProjectileComp;

	UPROPERTY(EditDefaultsOnly, Category = "Particle")
	UParticleSystem* ExplosionParticle;

public:
	FSphereTrace OnSphereTrace;

};
