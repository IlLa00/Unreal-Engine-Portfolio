#include "Game/CBGMManager.h"
#include "Global.h"
#include "Components/AudioComponent.h"
#include "DataAsset/CBGMDataAsset.h"

ACBGMManager::ACBGMManager()
{
	CHelpers::CreateSceneComponent(this, &AudioComp, "AudioComp");
	CheckNull(AudioComp);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_BGM");
	CheckNull(DataAsset);
}

void ACBGMManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBGMManager::SetBGM(FName Area)
{
	CheckNull(AudioComp);
	CheckNull(DataAsset);

	for (const auto& data : DataAsset->Datas)
	{
		if (Area == data.BGMName)
		{
			AudioComp->SetSound(data.BGM);
			PrintLine();
			break;
		}
	}

	AudioComp->Play();
}

