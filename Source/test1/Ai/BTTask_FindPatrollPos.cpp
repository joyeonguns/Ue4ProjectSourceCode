// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrollPos.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "NavigationSystem.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrollPos::UBTTask_FindPatrollPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrollPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	if (!ControllingPawn) {
		UE_LOG(LogTemp, Warning, TEXT("!ControllingPawn"));
		return EBTNodeResult::Failed;
	}

	// 내비 시스템 생성
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (!NavSystem) {
		UE_LOG(LogTemp, Warning, TEXT("!NavSystem"));
		return EBTNodeResult::Failed;
	}


	FVector targetPos;
	auto player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (player) {
		targetPos = player->GetActorLocation();
	}

	// UNavigationSystemV1을 통해 캐릭터 근처의 랜덤한 위치 생성
	FNavLocation NextPatrolPos;

	if (NavSystem->GetRandomPointInNavigableRadius(targetPos, 200.0f, NextPatrolPos)) {
		// 블랙보드의 PatrolPosKey 초기화
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemy_AIController::PatrolPosKey, NextPatrolPos.Location);

		return EBTNodeResult::Succeeded;
	}

	

	UE_LOG(LogTemp, Warning, TEXT("!Failed"));
	return EBTNodeResult::Failed;
}
