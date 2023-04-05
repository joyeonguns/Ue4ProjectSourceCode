// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	// 노드 이름
	NodeName = TEXT("TurnToTarget");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);


	// Enemy Target 설정
	auto Enemy = Cast<AEnemyBasic_Character>(OwnerComp.GetAIOwner()->GetPawn());

	if (!Enemy) return EBTNodeResult::Failed;

	auto Target = Cast<ATPS_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemy_AIController::TargetKey));

	if (!Target) return EBTNodeResult::Failed;

	// 캐릭터 방향 설정
	FVector LookVec = Target->GetActorLocation() - Enemy->GetActorLocation();
	LookVec.Z = 0.f;

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVec).Rotator();
	Enemy->SetActorRotation(FMath::RInterpTo(Enemy->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));




	return EBTNodeResult::Succeeded;
}

