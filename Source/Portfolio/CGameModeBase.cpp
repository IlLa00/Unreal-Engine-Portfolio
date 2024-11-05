#include "CGameModeBase.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "AbilitySystemGlobals.h"

ACGameModeBase::ACGameModeBase()
{
	UAbilitySystemGlobals::Get().InitGlobalData();

	// Set DefaultPawnClass
	TSubclassOf<ACPlayer> Player;
	CHelpers::GetClass(&Player, "/Script/Engine.Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
	CheckNull(Player);

	DefaultPawnClass = Player;
	
}
