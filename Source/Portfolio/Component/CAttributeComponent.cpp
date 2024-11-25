#include "Component/CAttributeComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

