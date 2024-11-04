#include "CGameModeBase.h"
#include "Global.h"
#include "Player/CPlayer.h"

ACGameModeBase::ACGameModeBase()
{
	// Set DefaultPawnClass
	TSubclassOf<ACPlayer> Player;
	CHelpers::GetClass(&Player, "/Script/Engine.Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
	CheckNull(Player);

	DefaultPawnClass = Player;
	
	
}
