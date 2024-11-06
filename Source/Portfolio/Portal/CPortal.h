#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPortal.generated.h"

class UBoxComponent;
class UParticleSystemComponent;
class UCPortalWidget;

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
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UBoxComponent* BoxComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Widget")
		TSubclassOf<UCPortalWidget> WidgetClass;

private:
	UCPortalWidget* PortalWidget;

};
