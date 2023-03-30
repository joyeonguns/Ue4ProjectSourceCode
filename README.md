# Ue4ProjectSourceCodedI
# UnrealEngine4를 통해 제작한 3인칭 액션 게임입니다.


## 프로젝트에 관한 정보
## 1. 게임 플로우 차트

![스크린샷 2023-03-31 052810](https://user-images.githubusercontent.com/85017198/228956615-da278aba-7889-4aa5-9b30-9af6976d4446.png)


## 2. 클래스 정보
### 2-1 클래스들의 역할
#### [Character 클래스]
**Basic_Character**

    ACharacter 클래스를 상속받는 가장 기본적인 캐릭터 클래스, 공통되는 TakeDamage, DieCharacter, Buff, DeBuff를 수행
                  
**TPS_Character**

    ABasic_Character를 상속 받음, 플래이어 캐릭터를 조종하는 클래스

**EnemyBasic_Character**

    ABasic_Character를 상속 받음, 적 캐릭터의 공통되는 속성을 모아 놓은 클래스, 캐릭터가 데미지를 입을 시 플로팅 데미지 출력, 사망시 포인트 획득
                        
**EnemyMelee_Character**

    AEnemyBasic_Character를 상속 받음, 적 캐릭터 중에서 근거리 공격을 수행하는 캐릭터 클래스

**EnemyRange_Character**

    AEnemyBasic_Character를 상속 받음, 적 캐릭터 중에서 원거리 공격을 수행하는 캐릭터 클래스, 화살을 스폰하여 발사


#### [Component 클래스]
**Character_Stat_Component** : UActorComponent를 상속받아 Basic_Character에 구성되는 클래스, 

                               캐릭터의 체력, 공격력, 특성 등의 정보를 제어한다. 


#### [Animation 클래스]
**TPSAnimInstance** : UAnimInstance를 상속받아 캐릭터의 애니메이션을 제어하는 클래스, 
  
                      애니메이션Notify를 통해 Delecate로 연결된 특정함수를 실행시킨다. 


#### [Actor 클래스]
**Weapon_Actor** : AAcor 클래스를 상속 받음, TPS_Character가 사용하는 무기 클래스로 공격시 플레이어의 정보를 받아 데미지를 준다.  

**Actor_GhostTail** : AAcor 클래스를 상속 받음, 캐릭터가 특정 행동을 취할시 잔상효과를 위해 생성된다.

**Actor_RewardBox** : AAcor 클래스를 상속 받음, 스테이지 클리어시 생성되는 보상상자이다. 

                  플레이어와 Overlap시 플레이어의 Interaction 델리케이트 함수를 활성화 시킨다.  
                  
**Actor_SpawnSkill_Q** : AAcor 클래스를 상속 받음, 플레이어가 스킬사용시 생성되어 적과 Overlap시 데미지를 준다.

**SPWArrow_Actor** : AAcor 클래스를 상속 받음, EnemyRange_Character가 공격시 생성되어 손에 부착된다. 

                  Shooting 함수를 통해 부착을 해제하고 타겟을 향해 날아간다.
                  
**LevelScriptActor_Battle** : ALevelScriptActor 클래스를 상속받아 레벨블루프린터의 부모클래스로 사용, 

                          게임플로우에 따라 적, UI, 보상 상자를 생성한다.


#### [PlayerController 클래스]
**TPSPlayerController** : APlayerController 클래스를 상속받음, 
                      전투레벨에서 사용하는 플레이어컨트롤러로 주로 UI를 생성및 제거하는 역할을 한다.
**TPSUI_PlayerController** : APlayerController 클래스를 상속받음, 
                      Title 레벨에서 사용하는 플레이어 컨트롤러 TitleUI 를 제어하기위해 사용한다.
**LoobyUIPlayerController** : APlayerController 클래스를 상속받음, 
                      Lobby 레벨에서 사용하는 플레이어 컨트롤러 LobbyUI 를 제어하기위해 사용한다.


#### [AI 클래스]
**Enemy_AIController** : AAIController 클래스를 상속받아 EnemyBasic_Character의 AiController로 사용된다. 
BTDecorator_CheckShocking
BTDecorator_IsinAttackRange
BTService_CheckAttackRange
BTService_CheckingShock
BTService_CheckShock
BTService_Detect
BTService_DetectPerception
BTTask_Attack
BTTask_FindPatrollPos
BTTask_TurnToTarget

#### [Userwidget 클래스]







CharacterStat_DataTable

Damage_Widget
FloatingDamage_Widget
HP_UserWidget
HUD_UserWidget
IngameMenu_UserWidget
Looby_UserWidget
Title_UserWidget
UserWidget_InGameData
UserWidget_LevelText

DataTable_StatLevel
DataTable_Status









Title_GameModeBase
LoobyGameModeBase
TPSGameModeBase

TPSGameInstance




















