#pragma once

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

class TagHelpers
{
public:
	static void AIChangeActionTag(FGameplayTagContainer& OutTagContainer, FName InTag)
	{

		OutTagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName(InTag)));
	}

	static void AIChangeStateTag(FGameplayTagContainer& OutTagContainer, FName InTag)
	{
		OutTagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName(InTag)));
	}

};