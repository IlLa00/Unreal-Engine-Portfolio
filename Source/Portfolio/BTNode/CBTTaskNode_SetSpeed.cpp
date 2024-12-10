#include "CBTTaskNode_SetSpeed.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCBTTaskNode_SetSpeed::UCBTTaskNode_SetSpeed()
{
	NodeName = "SetSpeed";
}

EBTNodeResult::Type UCBTTaskNode_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACharacter* Character = Cast<ACharacter>(OwnerComp.GetOwner());

	if (Character && Speed)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
	}

	return EBTNodeResult::Succeeded;
}
