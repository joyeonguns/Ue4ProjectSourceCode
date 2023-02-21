// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

const FName AEnemy_AIController::HomePosKey(TEXT("HomePos"));
const FName AEnemy_AIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AEnemy_AIController::TargetKey(TEXT("Target"));

AEnemy_AIController::AEnemy_AIController()
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
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::OnDetected);
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

void AEnemy_AIController::OnPossess(APawn* InPawn)
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
	Player = nullptr;

	for (auto actor : DetectedActor) {
		if (actor->ActorHasTag("Player")) {
			Player = Cast<ATPS_Character>(actor);
			UE_LOG(LogTemp, Warning, TEXT("FindPlayer"));
			if (Player)
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("ai distance : %f, %f"), Player->GetActorLocation().X, Player->GetActorLocation().Y));
			return;
		}
	}
}

void AEnemy_AIController::OnRepeatTimer()
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
