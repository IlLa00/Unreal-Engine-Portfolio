# Unreal Portfolio        
(대충 많은 걸 보여줄수있는 메인 스샷)             
GAS 프레임워크에 기반한 팰월드(오픈월드 서바이벌 / https://namu.wiki/w/Palworld) 모작으로 1인 제작된 간단한 싱글플레이 게임.    
엔진 : UE 5.2 / 에디터 : VS 2022 / 제작기간 : 2개월~     
포트폴리오 작업 연대기 : https://thoughtful-shop-228.notion.site/Unreal-12f894b38b10807ab856cce6331820f5?pvs=4    
# 기술 설명    
## 데이터 관리
<img src="https://github.com/user-attachments/assets/4edb563a-bde8-44bf-83f4-271fb6c70176" width="400px" height="100px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>    
- 코드의 큰 변경없이 쉽게 데이터 수정이 가능토록 데이터 에셋을 채택.    
- 데이터 에셋을 사용해 주로 고유의 **AttributeSet, 몽타주**들을 관리하고 데이터  내부에서 **TArray**를 사용해 확장성을 챙김.
## Level    
- **버추얼 텍스처 스트리밍**을 사용해 오픈월드의 대규모 환경 텍스쳐 로딩을 최적화.    
- 네비게이션 메시를 에디터에서 빌드하지 않고 **네비게이션 인보커**를 사용해 런타임에서 생성.
## Player
(대충 달리는 움짤)      
- 게임플레이 어빌리티(이하 GA) Sprint 발동 시, 스테미너가 서서히 감소하는 게임플레이 이펙트(이하 GE) 발동.      
(대충 소환하는 움짤)     
- GA Summon 발동 시, 펫 소환.     
- 점프도 넣을까?     
- 마우스 좌클릭 또는 우클릭 시, 현재 보유하고 있는 무기의 GA발동.
## Weapon
- 플레이어가 오너인 Equipment 클래스로 관리.
### Sword
- GA로 콤보 공격, 공격 시 스테미너가 감소하는 GE 발동.     
(대충 칼 사용하는 움짤)    
### Rifle
- GA로 0.1초마다 LineTraceSingleByObjectType() 실행.    
```c++
if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, Parms))
{
	ICAIInterface* AI = Cast<ICAIInterface>(HitResult.GetActor());
	CheckNull(AI);

	if (!AI->GetTagContainer().HasTag(FGameplayTag::RequestGameplayTag(FName("AI.Action.Dead"))))
	{
		AI->GetAIAttributeSet()->Attack(AI->GetAIAttributeSet()->GetCurrentHealth() - Rifle->GetAttiribute()->GetCurrentDamage(), GetOwningActorFromActorInfo());
  
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, HitResult.Location);
	}
}
```
(대충 총쏘는 움짤)    
### HookGun
- GA로 갈고리 총을 발사, 갈고리가 닿는 지점에 닿을시 캐릭터가 이동하면서 스테미너가 대폭 감소하는 GE 발동.    
(대충 갈고리총 사용하는 움짤)    
### ??? (Axe -> 유도탄발사기 바꾸는 중)
## AI
- AI는 기본적으로 **CAIInterface**를 상속받고 각자 고유의 AIController 빙의됨.   
- **NavigationInvokerComponent**로 객체 주변에 자동으로 네비게이션 메시 생성.    
- BehaviorTree의 Service노드에서 GamplayTag로 상태를 바꾸면서 Decorator_CheckTag에 따라 행동 결정.    
### Pet
- 플레이어 GA Summon으로 생성되고 삭제됨.        
- **AIPerceptionConfig_Sight**로 감지하며 보스와 몬스터 중에 보스를 우선순위로 타겟팅.     
<img src="https://github.com/user-attachments/assets/863c8212-6378-4976-9f7e-584e87489fc4" width="600px" height="400px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>    
(대충 펫이 행동하는 움짤)    
### Monster
- GameMode가 관리하는 Spawner 클래스로 스폰되며 SpawnActorDeferred로 데이터 에셋의 값들을 읽어와 몬스터들의 메시와 애님클래스가 설정된 뒤에 스폰됨.    
- 플레이어와 거리가 매우 멀어지면 삭제됨.    
- 각각 다른 메시를 가진 몬스터들은 모두 AttackCollision을 가지고 각기 다른 소켓에 위치해 있음. (공격 몽타주에 따라 달라짐.)    
- **AIPerceptionConfig_Sight**로 감지하며 플레이어와 펫중 플레이어를 우선순위로 타겟팅.    
<img src="https://github.com/user-attachments/assets/c7846b6e-ff96-4873-9a45-6f0d91de2540" width="600px" height="400px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>    
(대충 몬스터가 행동하는 움짤)    
#### Boss
- 지형에 1마리씩 배치, 레벨에 총 5마리가 스폰되어 있음.    
- 지면에 있을 때는 CharacterMovement를 사용하지만 공중에 있을 때는 **FloatingPawnMovement** 사용.          
-  **AIPerceptionConfig_Hearing**로 감지하며 플레이어와 펫 중 플레이어를 먼저 타깃으로 인식하게 설정.    
<img src="https://github.com/user-attachments/assets/4cf85110-4f49-4a36-a4c8-380f8657bb4f" width="600px" height="400px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>    
(대충 보스가 행동하는 움짤)
### Portal
- 플레이어와 오버랩 이벤트 발생 시, 포탈 위젯을 띄워 플레이어가 텔레포트 할 수 있게 함.    
- 실제 텔레포트 로직은 GameMode에서 실행.    
(대충 텔레포트 하는 움짤)
#### Item
- 몬스터나 보스가 죽으면 아이템을 드롭.
- 아이템의 종류에 따라 아이템을 먹을 시, 고유의 GE 발동.    
(대충 아이템 먹는 움짤)






 
