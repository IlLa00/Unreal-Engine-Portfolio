# Unreal Portfolio        
(대충 많은 걸 보여줄수있는 메인 스샷)             
GAS 프레임워크에 기반한 팰월드 모작으로 1인 제작된 간단한 싱글플레이 게임입니다.    
엔진 : UE 5.2 / 에디터 : VS 2022 / 제작기간 : 2개월~     
Notion : https://thoughtful-shop-228.notion.site/Unreal-12f894b38b10807ab856cce6331820f5?pvs=4        
# 들어가기 앞서,
팰월드라는 게임은 여러가지 장르들의 종합체(TPS, 생존, 오픈월드 등)입니다, 그만큼 복잡한 능력들을 처리해야하고 수많은 데이터들을 처리해야만 하므로 능력 기반 시스템을 구현하는데 강력한 GAS 프레임워크를 채택하였습니다.     
(대충 전체적인 흐름의 구조를 나타내는 그림) (대충 GAS 흐름을 나타내는 그림)   
# 기술 설명
> GAS 프레임워크를 적용해본만큼, GAS의 기능 위주로 설명하겠습니다.
## 목차   
[1. GAS의 Attribute와 데이터 에셋의 연동.](##-gas의-attribute와-데이터-에셋의-연동)     
[2. GAS의 GameplayTag와 AI들과의 연동.](##-gas의-gameplaytag와-ai들과의-연동)    
## GAS의 Attribute와 데이터 에셋의 연동
- 코드의 큰 변경없이 쉽게 데이터 수정이 가능해지는 유지보수성을 위해 데이터 에셋을 채택하였습니다.    
<img src="https://github.com/user-attachments/assets/4edb563a-bde8-44bf-83f4-271fb6c70176" width="400px" height="100px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>     
- 각각의 데이터 에셋은 공통적으로 **Attribute**와 연동되는 값(Base ~)들을 가지고있고 고유의 필요한 값들을 가지고 있습니다.
- 내부에서 **TArray**를 사용해 확장성을 챙겼습니다.       
<img src="https://github.com/user-attachments/assets/42ff1907-6a32-4b86-80bb-0f7a88e38a01" width="700px" height="500px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
-  Attribute를 가질 객체가 **스폰 될 때** 데이터 에셋의 값을 읽어서 적용합니다.
```c++
if (ASC && AIAttribute)
{
	AIAttribute->SetBaseHealth(DataAsset->Datas[Index].BaseHealth);
	AIAttribute->SetBaseDamage(DataAsset->Datas[Index].BaseDamage);

	AIAttribute->SetCurrentHealth(AIAttribute->GetBaseHealth());
	AIAttribute->SetCurrentDamage(AIAttribute->GetBaseDamage());
}
```
> 이런 방식으로 데이터 에셋에서 수치만 조절해도 코드에서 따로 수정할 필요가 없어 **유지보수가 용이**하고, 프로그래머 뿐만 아니라 다른 직군들도 쉽게 변경 가능케 해 **수월한 협업**을 기대해볼 수 있습니다.

## GAS의 GameplayTag와 AI들과의 연동
- AI들의 행동을 정의하는 태그들을 설정합니다.    
<img src="https://github.com/user-attachments/assets/93376070-1a88-42da-885c-895b3bdb2741" width="300px" height="150px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>    
- AI들은 BehaviorTree의 Service노드에서 조건에 따라 **GamplayTag**의 교체가 이루어지며 상태를 관리합니다.
> AI들은 Pet, Monster, Boss로 이루어져있으며 사진은 Pet의 BehaviorTree입니다.         
<img src="https://github.com/user-attachments/assets/863c8212-6378-4976-9f7e-584e87489fc4" width="600px" height="400px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
- 데코레이터 클래스를 상속받은 커스텀 클래스인 Decorator_TagCheck에 따라 AI들이 무슨 행동을 할 지 결정합니다.           
```c++
bool UCBTDecorator_TagCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner()->GetPawn()->GetClass()->ImplementsInterface(UCAIInterface::StaticClass()))
	{
		ICAIInterface* AI = Cast<ICAIInterface>(OwnerComp.GetAIOwner()->GetPawn());
		CheckNullResult(AI, false);

		return AI->GetTagContainer().HasTag(GameplayTag);
	}

	return false;
}
```
> AI의 행동들은 모두 GamplayAbility로 관리합니다.    
(대충 AI들이 행동하는 움짤)         
이렇게 GameplayTag로 상태와 능력을 관리합니다.
## GAS의 Ability를 가진 객체.    
### Player 
- Sprint, Jump, Summon(펫 소환) Ability를 보유합니다.
(대충 펫소환하는 움짤)
### Weapon 
- 각각 고유의 Ability를 보유하고 있으며, 플레이어가 어떤 무기를 들고있는지에 따라 발동하는 어빌리티가 다릅니다.          
  - Sword는 콤보 공격을 가능하게 하는 Ability를 보유하고 있습니다.(대충 콤보공격하는 움짤)
    - Sword와 충돌이 된 액터의 어트리뷰트는 Sword의 공격력 만큼 영향을 받습니다.             
  - Rifle은 0.1초마다 LineTrace를 진행하는 Ability를 보유하고 있습니다.(대충 총쏘는 움짤)
    - 라인트레이스에 영향을 받은 액터의 어트리뷰트가 Rifle의 공격력만큼 영향을 받습니다.
  - HookGun은 바라보고 있는 방향에 갈고리 총을 쏘고 지면에 닿으면 그 지점으로 날아가는 Ability를 보유하고 있습니다.(대충 갈고리총 쏘는 움짤)      
  - ?     
### AI 
- Attack, Dead Ability를 공통으로 보유하고 있고 Boss를 제외하고 GetHit Ability를 보유하고 있습니다. (대충 AI들이 공격하고 죽는 움짤)

## GameplayEffect와 Attribute와의 연동.
- 플레이어는 특정 어빌리티를 발동하면 스테미너가 감소하는 GameplayEffect가 발동됩니다.
> Sword의 Ability를 발동하는 사진입니다.     
<img src="https://github.com/user-attachments/assets/e78dd087-a56e-4144-a2b8-b4fc092d089c" width="1800px" height="300px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
- Sword의 AcivateAbility함수 내에서 GameplayEffect를 실행합니다.    
```c++
FGameplayEffectContextHandle EffectContext = Player->GetAbilitySystemComponent()->MakeEffectContext();
FGameplayEffectSpecHandle EffectSpecHandle = Player->GetAbilitySystemComponent()->MakeOutgoingSpec(BPDecreaseStaminaEffect, 1.0f, EffectContext);

Player->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), Player->GetAbilitySystemComponent());
```
- GameplayEffect가 정상적으로 실행이 되면 Stamina가 감소됩니다.    
(대충 뛰면 칼을 휘두르면 움짤)     

GameplayEffect는 블루프린트에서 만들어서 C++에 가져와 적용시키는 모습입니다, 데미지 처리도 GE를 통해서 구현할려고 했으나 모디파이어 설정에서 난항을 겪어 직접적으로 Attribute를 조절하게 되었습니다.       
## 그외 기술
### Level    
- **버추얼 텍스처 스트리밍**을 사용해 랜드스케이프 대규모 환경 텍스쳐 로딩을 최적화하여 텍스처 스트리밍 풀이 초과하는 오류를 해결하였습니다.(스샷추가)                  
- **네비게이션 인보커**를 사용해 런타임에서 네비게이션 메시를 필요한 만큼 생성하게 만들어 에디터에서 수많은 네비게이션 메시를 빌드하지 않게 했습니다, 이는 AI의 NavigationInvokerComponent와 이어집니다.(스샷추가?)         

## AI
- AI는 기본적으로 **CAIInterface**를 상속받아 인터페이스의 장점인 다형성과 코드의 재사용성을 이용해 유연한 코드를 구현해보았습니다.         
- **NavigationInvokerComponent**로 객체 주변에 자동으로 필요한만큼 네비게이션 메시를 생성합니다.
    
### Boss
- 공중에 떠있을 때 Z축을 크게 감지를 하지못하는 시각감지를 잘 쓰지 못하는 문제가 발생해 **AIPerceptionConfig_Hearing**으로 감지를 설정했습니다.
- **FloatingPawnMovementComponent**를 이용해 Boss가 공중에 뜨게 구현했습니다.
    
### Monster
- GameMode가 관리하는 Spawner 클래스로 스폰되며 **SpawnActorDeferred**로 데이터 에셋의 값들을 읽어와 몬스터들의 메시와 애님클래스가 설정된 뒤에 스폰됩니다.         
- **AIPerceptionConfig_Sight**로 감지하며 플레이어와 펫중 플레이어를 우선순위로 타겟팅.  

## Portal
- 플레이어와 오버랩 이벤트 발생 시, 포탈 위젯을 띄워 플레이어가 텔레포트 할 수 있게 함.    
- 실제 텔레포트 로직은 GameMode에서 실행.    
(대충 텔레포트 하는 움짤)

## Item
- 몬스터나 보스가 죽으면 아이템을 드롭.    
- 아이템의 종류에 따라 아이템을 먹을 시, 고유의 GE 발동.        
(대충 아이템 먹는 움짤)
