# Unreal Portfolio        
![스크린샷 2025-01-31 214715](https://github.com/user-attachments/assets/95a8d9ba-fe70-4d6c-aa9c-8cfd96d56753)               
**GAS 프레임워크**에 기반한 팰월드 모작으로 1인 제작된 간단한 싱글플레이 게임입니다.    
엔진 : UE 5.2 / 에디터 : VS 2022 / 제작기간 : 2개월~     
Notion : https://thoughtful-shop-228.notion.site/Unreal-12f894b38b10807ab856cce6331820f5?pvs=4        
# 들어가기 앞서,
팰월드라는 게임은 여러가지 장르들의 종합체(TPS, 생존, 오픈월드 등)입니다, 그만큼 복잡한 능력들을 처리해야하고 수많은 데이터들을 처리해야만 하므로 능력 기반 시스템을 구현하는데 강력한 GAS 프레임워크를 채택하였습니다.      
# 기술 설명
> GAS 프레임워크를 적용해본만큼, GAS의 기능 위주로 설명하겠습니다.
# 목차   
[1. GAS의 Attribute와 데이터 에셋의 연동.](#gas의-attribute와-데이터-에셋의-연동)     
[2. GAS의 GameplayTag와 AI들과의 연동.](#gas의-gameplaytag와-ai들과의-연동)      
[3. GAS의 Ability를 가진 객체.](#gas의-ability를-가진-객체)     
[4. GameplayEffect와 Attribute와의 연동.](#gameplayeffect와-attribute와의-연동)     
[5. GameplayEffect와 GameplayCue와의 연동.](#gameplayeffect와-gameplaycue와의-연동).
  
[그 외 기술](#그외-기술)
## GAS의 Attribute와 데이터 에셋의 연동.
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
![1-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/475dd146-60ad-4fcb-98b4-0f18538b33b3)        
> AI의 행동들은 모두 GamplayAbility로 관리합니다.                 
이렇게 GameplayTag로 상태와 능력을 관리합니다.
## GAS의 Ability를 가진 객체.    
### Player 
- Sprint, Jump, Summon(펫 소환) Ability를 보유합니다.
(대충 펫소환하는 움짤)
### Weapon 
- 각각 고유의 Ability를 보유하고 있으며, 플레이어가 어떤 무기를 들고있는지에 따라 발동하는 어빌리티가 다릅니다.          
  - Sword는 콤보 공격을 가능하게 하는 Ability를 보유하고 있습니다.
    ![bandicam2025-02-0920-45-06-406-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/e4f23f45-0514-4edb-8ef4-76aac524966c)         
    - Sword와 충돌이 된 액터의 어트리뷰트는 Sword의 공격력 만큼 영향을 받습니다.             
  - Rifle은 0.1초마다 LineTrace를 진행하는 Ability를 보유하고 있습니다.        
    ![bandicam2025-02-0920-54-48-016-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/25e29c49-3053-45ac-9c7a-76eca9500bf1)         
    - 라인트레이스에 영향을 받은 액터의 어트리뷰트가 Rifle의 공격력만큼 영향을 받습니다.
  - HookGun은 바라보고 있는 방향에 갈고리 총을 쏘고 지면에 닿으면 그 지점으로 날아가는 Ability를 보유하고 있습니다.              
    ![bandicam2025-02-0921-56-59-360-ezgif com-video-to-gif-converter (1)](https://github.com/user-attachments/assets/2460d136-08b3-415d-8c05-c08a21be6c42)       
  - RPG는 몬스터와 닿으면 주변에 SphereTrace를 진행하는 로켓을 발사하는 Ability를 보유하고 있습니다.      
    ![bandicam2025-02-0922-23-34-677-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/f7095deb-9f2c-4d5f-89f9-f11226203f7e)       
 
### AI 
- Attack, Dead Ability를 공통으로 보유하고 있고 Boss를 제외하고 GetHit Ability를 보유하고 있습니다.
![bandicam2025-02-0922-41-25-118-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/78c57001-46a0-4277-8d3a-b33a6d9b12cf)        
## GameplayEffect와 Attribute와의 연동.
> 플레이어가 Sprint 어빌리티를 발동하면 발생되는 C++ GameplayEffect 입니다.    
```c++
UGE_DecreaseStamina::UGE_DecreaseStamina()
{
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo Modifier;
    Modifier.Attribute = FGameplayAttribute(FindFieldChecked<FProperty>(
        UCCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCCharacterAttributeSet, CurrentStamina)
    ));

    Modifier.ModifierOp = EGameplayModOp::Additive;  
    Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(-5.f); 

    Modifiers.Add(Modifier);
}
```      
- 플레이어의 Sprint 어빌리티 AcivateAbility함수 내에서 C++을 상속받은 블루프린트의 GameplayEffect를 실행합니다.    
```c++
FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(BPMovementEffect, 1.0f, EffectContext);

ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
```
- GameplayEffect가 정상적으로 실행이 되면 Stamina가 감소됩니다.
![bandicam2025-02-0922-56-08-109-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/87228e25-69d9-43e7-951c-f480c889a13d)      


## GameplayEffect와 GameplayCue와의 연동.   
- 특정 GameplayEffect가 발생되면 GameplayEffect 클래스에서 지정된 **GameplayCue Tag**가 호출됩니다.
- **GameplayCue Tag**가 호출되면, **GameplayCue Notfiy Static**을 상속받은 **GameplayCue**가 발동됩니다.       
> 몬스터를 처치 시, 스폰되는 힐 버프 아이템을 획득하면 Heal GameEffect가 발생되며 파티클이 재생되는 **GameplayCue**가 호출됩니다.    
![bandicam2025-02-0923-10-30-030-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/6f557243-17af-4dc8-9a50-253a82118c39)     
## 그외 기술
### Level    
- **버추얼 텍스처 스트리밍**을 사용해 랜드스케이프 대규모 환경 텍스쳐 로딩을 최적화하여 텍스처 스트리밍 풀이 초과하고 픽셀이 깨지는 오류를 해결하였습니다.                 
- **네비게이션 인보커**를 사용해 런타임에서 네비게이션 메시를 필요한 만큼 생성하게 만들어 에디터에서 수많은 네비게이션 메시를 빌드하지 않게 했습니다, 이는 AI의 NavigationInvokerComponent와 이어집니다.        
<img src="https://github.com/user-attachments/assets/4df9a1aa-eca8-4474-940f-b0058c7c0f83" width="800px" height="400px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>       
<img src="https://github.com/user-attachments/assets/2e9d93c0-24c6-4e5b-834d-6ca38868e716" width="400px" height="100px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>      
<img src="https://github.com/user-attachments/assets/c7746e40-52f7-4cc2-bd5c-8fdc92a9d6c8" width="800px" height="400px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>      
### Item - Inventory
- 데이터 테이블을 이용해 아이템들의 정보를 읽고 몬스터나 보스가 죽으면 아이템이 스폰되며 플레이어와 오버랩 시, 아이템이 인벤토리에 들어갑니다.
- **아이템의 정보를 담는 TMap** 하나와, **수량정보를 담당하는 TMap** 하나를 이용하여 빠른 검색 기능을 이용해 동일한 아이템이 들어오면 수량정보를 담당하는 TMap의 Value값을 올리고, 새로운 아이템이 들어오면 두개의 TMap에 새로운 값을 넣습니다. (영상수정해야됨)                        
![bandicam2025-02-1000-16-40-566-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/185d723a-5802-4f22-9b1b-99a14c0a82b3)
```c++
void UCInventory::AddItemToInventory(const FItemDataTable Row)
{
	if (Row.Name.IsValid())
	{
		if (ItemDatas.Contains(Row.Name)) 
		{
			int32* Count = ItemCount.Find(Row.Name);

			++(*Count); 

			ItemCount.Emplace(Row.Name, *Count);
		}
		else 
		{
			int32 Count = 1;

			ItemDatas.Emplace(Row.Name, Row);
			ItemCount.Emplace(Row.Name, Count);
		}
	}
}
```      
### AI
- AI는 기본적으로 **CAIInterface**를 상속받아 인터페이스의 장점인 다형성과 코드의 재사용성을 이용해 유연한 코드를 구현해보았습니다.         
- **NavigationInvokerComponent**로 객체 주변에 자동으로 필요한만큼 네비게이션 메시를 생성합니다.      
<img src="https://github.com/user-attachments/assets/907520c6-9f44-4946-98d3-ea2f2f6b820d" width="600px" height="100px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
<img src="https://github.com/user-attachments/assets/27c1f77c-6f31-4339-a984-82121126e565" width="600px" height="200px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
<img src="https://github.com/user-attachments/assets/fc11cce6-b949-4e52-95a8-b506e5ae24eb" width="600px" height="200px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>


    
### Boss
- 공중에 떠있을 때 Z축을 크게 감지를 하지못하는 시각감지를 잘 쓰지 못하는 문제가 발생해 **AIPerceptionConfig_Hearing**으로 감지를 설정했습니다.
- **FloatingPawnMovementComponent**를 이용해 Boss가 공중에 뜨게 구현했습니다.      
![bandicam2025-02-1000-01-08-621-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/bedf2ea9-8b5c-4acb-8182-e6a80e0fe167)          
![bandicam2025-02-1000-07-53-750-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/e7d6451a-28bc-42e1-af55-eeeac9614186)         

### Monster
- GameMode가 관리하는 Spawner 클래스로 스폰되며 **SpawnActorDeferred**로 데이터 에셋의 값들을 읽어와 몬스터들의 메시와 애님클래스가 설정된 뒤에 스폰됩니다.
- SetMesh(FName Area)라는 커스텀 함수로 플레이어가 속한 지형에 따라 스폰되는 몬스터의 메시를 조정합니다.     
```c++
ACMonster* Monster = GetWorld()->SpawnActorDeferred<ACMonster>(MonsterClass, SpawnTM);
CheckNull(Monster);

Monster->SetMesh(PlayerArea);
EnemyController->Possess(Monster);

Monster->FinishSpawning(SpawnTM);
```         
- **AIPerceptionConfig_Sight**로 감지하며 플레이어와 펫중 플레이어를 우선순위로 타겟팅합니다.  

### Portal
- 플레이어와 오버랩 이벤트 발생 시, 특정 지형으로 이동할 수 있게하는 위젯을 띄웁니다.        
- 실제 텔레포트 로직은 GameMode에서 실행합니다.      
![bandicam2025-02-1000-29-54-829-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/ceafd9ef-8347-4349-ab9d-1ab3ee7f66a9)      
