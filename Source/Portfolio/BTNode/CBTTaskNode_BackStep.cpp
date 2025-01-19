#include "CBTTaskNode_BackStep.h"
#include "Global.h"
#include "Pet/CPetController.h"
#include "Pet/CPet.h"
#include "GameFramework/CharacterMovementComponent.h"

UCBTTaskNode_BackStep::UCBTTaskNode_BackStep()
{
	NodeName = "BackStep";

	CHelpers::GetAsset(&BackStepMontage, "/Game/Assets/BattleWizardPolyart/Animations/JumpAnim_Montage");
	CheckNull(BackStepMontage);

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_BackStep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
	CheckNullResult(Pet, EBTNodeResult::Failed);

	Pet->PlayAnimMontage(BackStepMontage);

	FVector BackwardDirection = -1 * Pet->GetActorForwardVector();
	FVector JumpVelocity = BackwardDirection * 10000.f;

	Pet->GetCharacterMovement()->Launch(BackwardDirection * JumpVelocity);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_BackStep::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACPetController* AIC = Cast<ACPetController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	ACPet* Pet = Cast<ACPet>(AIC->GetPawn());
	CheckNull(Pet);

	if (!Pet->GetCurrentMontage())
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}
