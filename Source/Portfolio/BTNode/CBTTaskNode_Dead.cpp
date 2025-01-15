#include "CBTTaskNode_Dead.h"
#include "Global.h"
#include "AIController.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GAS/GA/AI_Dead.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UCBTTaskNode_Dead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner()->GetPawn()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
		CheckNullResult(ASI, EBTNodeResult::Failed);

		if(OwnerComp.GetAIOwner()->GetCharacter()->GetCurrentMontage())
			OwnerComp.GetAIOwner()->GetCharacter()->StopAnimMontage();
		
		ASI->GetAbilitySystemComponent()->TryActivateAbility(ASI->GetAbilitySystemComponent()->FindAbilitySpecFromClass(UAI_Dead::StaticClass())->Handle);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
