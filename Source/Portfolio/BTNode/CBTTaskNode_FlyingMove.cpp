#include "CBTTaskNode_FlyingMove.h"
#include "Global.h"

EBTNodeResult::Type UCBTTaskNode_FlyingMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UCBTTaskNode_FlyingMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}

EBTNodeResult::Type UCBTTaskNode_FlyingMove::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}
