// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	bIsAttacking = false;
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto Enemy = Cast<AEnemyBasic_Character>(OwnerComp.GetAIOwner()->GetPawn());
	if(!Enemy) return EBTNodeResult::Failed;
	
	// 공격 함수 호출
	Enemy->Attack();
	bIsAttacking = true;

	// OnAttackEnd 호출시 bIsAttacking = false;
	Enemy->OnAttackEnd.Clear();
	Enemy->OnAttackEnd.AddLambda([this]() -> void {
		bIsAttacking = false;
		});

	// Task 상태 진행중
	return EBTNodeResult::InProgress;
}


void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaTime);

	// Task 완료
	if (!bIsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
