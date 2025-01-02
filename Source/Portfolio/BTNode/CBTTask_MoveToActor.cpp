#include "CBTTask_MoveToActor.h"
#include "Global.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UCBTTask_MoveToActor::UCBTTask_MoveToActor()
{
	NodeName = "MoveToActor";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTask_MoveToActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(BlackboardKey.IsSet())
		return EBTNodeResult::InProgress;

    return EBTNodeResult::Failed;
}

void UCBTTask_MoveToActor::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
        {
            UObject* KeyValue = BlackboardComp->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
            if (KeyValue)
            {
                AActor* TargetActor = Cast<AActor>(KeyValue);
                if (TargetActor)
                {
                    OwnerComp.GetAIOwner()->MoveToActor(TargetActor);
                    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                }
            }
        }
        else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
        {
            FVector TargetLocation = BlackboardComp->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
           
            OwnerComp.GetAIOwner()->MoveToLocation(TargetLocation);
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        }
    }
}

EBTNodeResult::Type UCBTTask_MoveToActor::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Aborted;
}
