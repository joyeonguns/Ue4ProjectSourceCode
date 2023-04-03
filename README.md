# Ue4ProjectSourceCodedI
# UnrealEngine4를 통해 제작한 3인칭 액션 게임입니다.

개발 일지 : https://blog.naver.com/kingultra45/223020414038

동영상   :

![Title](https://user-images.githubusercontent.com/85017198/228983652-e549073d-c6f2-4077-b987-5613d767df17.png)
![Lobby](https://user-images.githubusercontent.com/85017198/228983675-6145a17d-3f4e-49f6-a414-ec2c2db13a4a.png)
![InGame](https://user-images.githubusercontent.com/85017198/228983872-ac1cfd2c-78a4-4490-920d-d9a4dd0e3e8a.png)


## 프로젝트에 관한 정보
## 1. 게임 플로우 차트
<details>
    <summary>자세히</summary>


![flow](https://user-images.githubusercontent.com/85017198/229432749-0a15e4c8-eec1-49df-b7d0-cc7f2784c60e.png)

</details>
    
## 2. 클래스 정보
### 2-1 클래스들의 역할
### [Character 클래스]
<details>
    <summary>자세히</summary>


**Basic_Character**

    ACharacter 클래스를 상속받는 가장 기본적인 캐릭터 클래스, 공통되는 TakeDamage, DieCharacter, Buff, DeBuff를 수행
                  
**TPS_Character**

    ABasic_Character를 상속 받음, 플래이어 캐릭터를 조종하는 클래스

**EnemyBasic_Character**

    ABasic_Character를 상속 받음, 적 캐릭터의 공통되는 속성을 모아 놓은 클래스, 
    캐릭터가 데미지를 입을 시 플로팅 데미지 출력, 사망시 포인트 획득
                        
**EnemyMelee_Character**

    AEnemyBasic_Character를 상속 받음, 적 캐릭터 중에서 근거리 공격을 수행하는 캐릭터 클래스

**EnemyRange_Character**

    AEnemyBasic_Character를 상속 받음, 적 캐릭터 중에서 원거리 공격을 수행하는 캐릭터 클래스, 화살을 스폰하여 발사


</details>

### [Component 클래스]
<details>
    <summary>자세히</summary>
    
    
**Character_Stat_Component**

    UActorComponent를 상속받아 Basic_Character에 구성되는 클래스, 캐릭터의 체력, 공격력, 특성 등의 정보를 제어한다. 

    
</details>
    
### [Animation 클래스]
**TPSAnimInstance**

    UAnimInstance를 상속받아 캐릭터의 애니메이션을 제어하는 클래스, 애니메이션Notify를 통해 Delecate로 연결된 특정함수를 실행시킨다. 


### [Actor 클래스]
<details>
    <summary>자세히</summary>
    
    
**Weapon_Actor** 

    AAcor 클래스를 상속 받음, TPS_Character가 사용하는 무기 클래스로 공격시 플레이어의 정보를 받아 데미지를 준다.  

**Actor_GhostTail** 

    AAcor 클래스를 상속 받음, 캐릭터가 특정 행동을 취할시 잔상효과를 위해 생성된다.

**Actor_RewardBox**

    AAcor 클래스를 상속 받음, 스테이지 클리어시 생성되는 보상상자이다. 
    플레이어와 Overlap시 플레이어의 Interaction 델리케이트 함수를 활성화 시킨다.  
                  
**Actor_SpawnSkill_Q** 

    AAcor 클래스를 상속 받음, 플레이어가 스킬사용시 생성되어 적과 Overlap시 데미지를 준다.

**SPWArrow_Actor**

    AAcor 클래스를 상속 받음, EnemyRange_Character가 공격시 생성되어 손에 부착된다. 
    Shooting 함수를 통해 부착을 해제하고 타겟을 향해 날아간다.
                  
**LevelScriptActor_Battle**

    ALevelScriptActor 클래스를 상속받아 레벨블루프린터의 부모클래스로 사용, 게임플로우에 따라 적, UI, 보상 상자를 생성한다.

</details>
    
### [PlayerController 클래스]
<details>
    <summary>자세히</summary>
    
    
**TPSPlayerController** :

    APlayerController 클래스를 상속받음, 전투레벨에서 사용하는 플레이어컨트롤러로 주로 UI를 생성및 제거하는 역할을 한다.
    
**TPSUI_PlayerController** 

    APlayerController 클래스를 상속받음, Title 레벨에서 사용하는 플레이어 컨트롤러 TitleUI 를 제어하기위해 사용한다.
    
**LoobyUIPlayerController**

    APlayerController 클래스를 상속받음, Lobby 레벨에서 사용하는 플레이어 컨트롤러 LobbyUI 를 제어하기위해 사용한다.

</details>
    
### [AI 클래스]
<details>
    <summary>자세히</summary>
    

**Enemy_AIController**
    
    AAIController 클래스를 상속받아 EnemyBasic_Character의 AiController로 사용된다. UAISenseConfig_Sight를 통해 플레이어를 감지한다. 
    BehaviorTree를 통해 EnemyBasic_Character를 상속받는 캐릭터의 움직임을 제어한다.
    
**BTDecorator_CheckShocking**
    
    UBTDecorator 클래스를 상속받음, BehaviorTree의 노드에 부착하여 해당시점에 캐릭턱가 충격을 받은 상태인지 판단한다.
    실시간으로 충격상태를 판단할 수 없어 사용하지 못함
    
**BTDecorator_IsinAttackRange**
    
    UBTDecorator 클래스를 상속받음, BehaviorTree의 노드에 부착하여 해당시점에서 캐릭터의 공격범위에 타겟이 있는지 판단한다.
    
**BTService_CheckAttackRange**
    
    UBTService 클래스를 상속받음, BehaviorTree 노드에 부착하여 매초마다 감지한다.
    캐릭터의 공격범위에 타겟이 있는지 확인하여 Blackboard의 bCanAttack의 값을 초기화한다.
    
**BTService_CheckShock**
    
    UBTService 클래스를 상속받음, BehaviorTree 노드에 부착하여 0.2초마다 감지한다. 
    캐릭터가 충격을 받은 상태인지 확인하여 Blackboard의 bShocking 값을 초기화한다.
   
**BTService_Detect**
    
    UBTService 클래스를 상속받음, BehaviorTree 노드에 부착하여 매초마다 감지한다.
    FCollisionQueryParams를 통해 캐릭터 주변에 타겟이 있는지 감지하여 Blackboard의 Target 값을 초기화한다.
    AIPercetion 방식을 채택하여 사용하지 않는다.
    
**BTService_DetectPerception**
    
    UBTService 클래스를 상속받음, BehaviorTree 노드에 부착하여 매초마다 감지한다.
    AIPercetion을 사용하여 캐릭터가 타겟을 발견하였는지 감지하여 Blackboard의 Target 값을 초기화한다.
    
**BTTask_Attack**
    
    UBTTaskNode 클래스를 상속받음, BehaviorTree에서 사용할 노드이다.
    캐릭터의 공격함수를 호출하고 공격이 끝나면 리턴값을 Succeeded 해 준다.
    
**BTTask_FindPatrollPos**
    
    UBTTaskNode 클래스를 상속받음, BehaviorTree에서 사용할 노드이다.
    UNavigationSystemV1를 통해 캐릭터를 이동시킬 랜덤한 좌표를 얻어 Blackboard의 PatrolPos를 초기화한다. 
    
**BTTask_TurnToTarget**
    
    UBTTaskNode 클래스를 상속받음, BehaviorTree에서 사용할 노드이다.
    캐릭터가 공격하는 동안 FRotationMatrix를 통해 캐릭터의 Rotation을 변경한다.
    

</details>
    
### [Userwidget 클래스]
<details>
    <summary>자세히</summary>
    
**Title_UserWidget**
        
    UserWidget클래스를 상속 받음, 타이레벨의 UI로 게임시작시 로비레벨로 게임종료시 게임을 나가게 한다.    

**Looby_UserWidget**
    
    UserWidget클래스를 상속 받음, 로비레벨의 UI로 게임시작 전 설정(텔런트, 속성)을 셋팅 및 게임 정보(버프, 디버프)를 확인할 수 있다.    
    
**HP_UserWidget**
    
    UserWidget클래스를 상속 받음, EnemyBasic_Character를 상속받는 캐릭터가 데미지를 입을 시 생성
    해당 캐릭터의 체력바를 10초간 띄워준다.
        
**FloatingDamage_Widget**
    
    UserWidget클래스를 상속 받음, EnemyBasic_Character를 상속받는 캐릭터가 데미지를 입을 시 생성
    해당 캐릭터의 위치를 스크린 좌표로 변경하고 캐릭터가 입은 피해를 띄워준다.

**HUD_UserWidget**
    
    UserWidget클래스를 상속 받음 전투레벨에서 사용하는 UI
    플레이어 캐릭터의 정보(체력, 스킬 및 아이템의 쿨타임, 포인트)를 띄워준다,
    
**IngameMenu_UserWidget**
        
    UserWidget클래스를 상속 받음 전투레벨에서 사용하는 UI
    전투 레벨에서 ESC 액션을 누르면 게임을 정지하고 게임을 계속할지 그만둘지 선택할 수 있는 UI
  
**UserWidget_InGameData**
    
    UserWidget클래스를 상속 받음 전투레벨에서 사용하는 UI
    전투 레벨에서 TAP 액션을 누르면 스테이지의 정보와 캐릭터의 정보를 보여준다.
        
**UserWidget_LevelText**
    
    UserWidget클래스를 상속 받음 전투레벨에서 사용하는 UI
    LevelScriptActor_Battle 클래스에서 해당 스테이지에 대한 정보를 보여준다.

</details>


### [게임인스턴스 구조체]
**TPSGameInstance**

    UGameInstance를 상속받음, 레벨이 바뀌어도 초기화되지 않는 싱글턴 형식의 객체이다.
    게임에 필요한 데이터들을 관리하고 데이터 테이블과 데이터 구조체를 연결하여 제공한다.
    
### 2-2 클래스들의 UML

### [캐릭터 클래스 UML]
![uml](https://user-images.githubusercontent.com/85017198/228981431-d4ff23e4-f456-43da-ac15-c048c0db768e.png)

### [캐릭터 클래스 UML]
![uml2](https://user-images.githubusercontent.com/85017198/228981607-ec2e1d38-0334-4908-895a-5c451eb45171.png)
