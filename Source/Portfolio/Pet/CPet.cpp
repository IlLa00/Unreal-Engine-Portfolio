#include "CPet.h"
#include "Global.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Components/TextRenderComponent.h"
#include "CPetController.h"
#include "GAS/GA/AI_Attack.h"
#include "GAS/GA/AI_GetHit.h"
#include "GAS/GA/AI_Dead.h"
#include "GAS/Attribute/CAIAttributeSet.h"
#include "DataAsset/CPetDataAsset.h"
#include "Widget/CPetWidget.h"

ACPet::ACPet()
{
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Assets/BattleWizardPolyart/Meshes/WizardSM");
	CheckNull(MeshAsset);

	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	CHelpers::CreateSceneComponent(this, &TextComp, "TextComp", GetMesh());
	CheckNull(TextComp);

	TextComp->SetRelativeLocation(FVector(0, 0, 200));
	TextComp->SetRelativeRotation(FRotator(0, 90, 0));
	TextComp->SetHorizontalAlignment(EHTA_Center);

	CHelpers::GetClass(&AnimClass, "/Game/Pet/ABP_CPet");
	CheckNull(AnimClass);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	CheckNull(ASC);

	AIAttribute = CreateDefaultSubobject<UCAIAttributeSet>("Attribute");
	CheckNull(AIAttribute);

	CHelpers::GetAsset(&DataAsset, "/Game/DataAsset/DA_Pet");
	CheckNull(DataAsset);

	CHelpers::GetClass(&PetWidgetClass, "/Game/Widget/BP_CPetWidget");
	CheckNull(PetWidgetClass);
}

void ACPet::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetAnimClass(AnimClass);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACPetController::StaticClass();

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	ASC->InitAbilityActorInfo(this, this);

	FGameplayAbilitySpec AttackSpec(UAI_Attack::StaticClass());
	ASC->GiveAbility(AttackSpec);

	FGameplayAbilitySpec HitSpec(UAI_GetHit::StaticClass());
	ASC->GiveAbility(HitSpec);

	FGameplayAbilitySpec DeadSpec(UAI_Dead::StaticClass());
	ASC->GiveAbility(DeadSpec);

	if (AIAttribute)
	{
		AIAttribute->SetBaseHealth(DataAsset->BaseHealth);
		AIAttribute->SetBaseDamage(DataAsset->BaseDamage);
		AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
		AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
	}

	PetWidget = CreateWidget<UCPetWidget>(GetWorld(), PetWidgetClass);
	CheckNull(PetWidget);
	PetWidget->AddToViewport();

}

void ACPet::Tick(float DeltaTime)
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

UAbilitySystemComponent* ACPet::GetAbilitySystemComponent() const
{
	return ASC;
}

