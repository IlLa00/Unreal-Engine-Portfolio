#include "BTNode/CEnvQueryContext_Player.h"
#include "Global.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/CPlayer.h"

void UCEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	ACharacter* Querier = Cast<ACharacter>(QueryInstance.Owner.Get());
	if (Querier && Querier->GetController() && Cast<AAIController>(Querier->GetController())) // 컨트롤러의 블랙보드에 읽힌 플레이어 리턴
	{
		AAIController* AIC = Cast<AAIController>(Querier->GetController());
		if (AIC->GetBlackboardComponent())
		{
			ACPlayer* Player = Cast<ACPlayer>(AIC->GetBlackboardComponent()->GetValueAsObject("PlayerKey"));
			if (Player)
			{
				UEnvQueryItemType_Actor::SetContextHelper(ContextData, Player);
				return;
			}
		}
	}
	return;
	// UEnvQueryItemType_Actor::SetContextHelper(ContextData, UGameplayStatics::GetPlayerPawn(Querier->GetWorld(), 0));
}