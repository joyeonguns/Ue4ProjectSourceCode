// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// 블랙보드 변수 
const FName AEnemy_AIController::HomePosKey(TEXT("HomePos"));
const FName AEnemy_AIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AEnemy_AIController::TargetKey(TEXT("Target"));
const FName AEnemy_AIController::TargetPosKey(TEXT("TargetPos"));
const FName AEnemy_AIController::bCanAttackKey(TEXT("bCanAttack"));
const FName AEnemy_AIController::bShockKey(TEXT("bShocking"));


AEnemy_AIController::AEnemy_AIController()
{
	PrimaryActorTick.bCanEverTick = true;

	// AI Perception 제작
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight_Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	
	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());

	// 감지 
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::OnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);


	// FObjectFinder로 블랙보드 연결
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/BeHaviorTree/BB_EnemyAiBoard.BB_EnemyAiBoard'"));
	if (BBObject.Succeeded()) {
		BBAsset = BBObject.Object;
	}

	// FObjectFinder BehaviorTree 연결
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/BeHaviorTree/BT_EnemyAiTree.BT_EnemyAiTree'"));
	if (BTObject.Succeeded()) {
		BTAsset = BTObject.Object;
	}

	RepeatIntervar = 3.0f;
}

void AEnemy_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// 블랙보드 HomePosKey 변수 초기화
	if (UseBlackboard(BBAsset, Blackboard)) {
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());

		if (!RunBehaviorTree(BTAsset)) {
			UE_LOG(LogTemp, Warning, TEXT("!RunBehaviorTree(BTAsset)"));
		}
	}

}

void AEnemy_AIController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(ReapeatTimeHandler);
}

void AEnemy_AIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetPerceptionComponent() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("GetPerceptionComponent"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("!GetPerceptionComponent"));
	}

}

void AEnemy_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ATPS_Character* AEnemy_AIController::GetPlayer()
{
	return Player;
}

void AEnemy_AIController::OnDetected(const TArray<AActor*> &DetectedActor)
{
	// 타겟 설정
	for (auto actor : DetectedActor) {
		if (actor->ActorHasTag("Player")) {
			Player = Cast<ATPS_Character>(actor);
			UE_LOG(LogTemp, Warning, TEXT("FindPlayer"));
			return;
		}
	}
}

void AEnemy_AIController::Setplayer(class ATPS_Character* _player)
{
	Player = _player;
}


