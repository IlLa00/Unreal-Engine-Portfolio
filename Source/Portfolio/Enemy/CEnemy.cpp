#include "CEnemy.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Components/TextRenderComponent.h"
#include "DataAsset/CMonsterMeshDataAsset.h"
#include "GAS/Attribute/CMonsterAttributeSet.h"
#include "CEnemyController.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &TextComp, "TextComp", GetMesh());
	CheckNull(TextComp);

	TextComp->SetRelativeLocation(FVector(0, 0, 200));
	TextComp->SetRelativeRotation(FRotator(0, 90, 0));
	TextComp->SetHorizontalAlignment(EHTA_Center);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Monster");
	CheckNull(DataAsset);

	Attribute = CreateDefaultSubobject<UCMonsterAttributeSet>("Attribute");
	CheckNull(Attribute);

}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACEnemyController::StaticClass();

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	ASC->InitAbilityActorInfo(this, this);

	TagContainer.AddTag(FGameplayTag::RequestGameplayTag("AI.State.Idle"));

}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TagContainer.Num() > 0)
	{
		for (const FGameplayTag& Tag : TagContainer)
		{
			TextComp->SetText(FText::FromString(Tag.ToString()));
		}
	}
}

UAbilitySystemComponent* ACEnemy::GetAbilitySystemComponent() const
{
	return ASC;
}

