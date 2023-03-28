// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController2.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

const FName AEnemyAIController2::HomePosKey(TEXT("HomePos"));
const FName AEnemyAIController2::PatrolPosKey(TEXT("PatrolPos"));
const FName AEnemyAIController2::TargetKey(TEXT("Target"));
const FName AEnemyAIController2::TargetPosKey(TEXT("TargetPos"));
const FName AEnemyAIController2::bCanAttackKey(TEXT("bCanAttack"));


AEnemyAIController2::AEnemyAIController2()
{
	PrimaryActorTick.bCanEverTick = true;

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
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController2::OnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);



	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/BeHaviorTree/BB_EnemyAiBoard.BB_EnemyAiBoard'"));
	if (BBObject.Succeeded()) {
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/BeHaviorTree/BT_EnemyAiTree.BT_EnemyAiTree'"));
	if (BTObject.Succeeded()) {
		BTAsset = BTObject.Object;
	}

	RepeatIntervar = 3.0f;
}

void AEnemyAIController2::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//GetWorld()->GetTimerManager().SetTimer(ReapeatTimeHandler, this, &AEnemy_AIController::OnRepeatTimer, RepeatIntervar, true);

	if (UseBlackboard(BBAsset, Blackboard)) {
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());

		if (!RunBehaviorTree(BTAsset)) {
			UE_LOG(LogTemp, Warning, TEXT("!RunBehaviorTree(BTAsset)"));
		}
	}

}

void AEnemyAIController2::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(ReapeatTimeHandler);
}

void AEnemyAIController2::BeginPlay()
{
	Super::BeginPlay();
	if (GetPerceptionComponent() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("GetPerceptionComponent"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("!GetPerceptionComponent"));
	}

}

void AEnemyAIController2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ATPS_Character* AEnemyAIController2::GetPlayer()
{
	return Player;
}

void AEnemyAIController2::OnDetected(const TArray<AActor*>& DetectedActor)
{
	//Player = nullptr;

	for (auto actor : DetectedActor) {
		if (actor->ActorHasTag("Player")) {
			Player = Cast<ATPS_Character>(actor);
			UE_LOG(LogTemp, Warning, TEXT("FindPlayer"));
			return;
		}
	}
}

void AEnemyAIController2::OnRepeatTimer()
{

	auto CurrentPawn = GetPawn();
	if (CurrentPawn) {
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

		if (!NavSystem) {
			UE_LOG(LogTemp, Warning, TEXT("!NavSystem"));
			return;
		}

		FNavLocation NextLocation;
		// ·£´ý ÀÌµ¿
		if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation)) {
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		}
	}





}
