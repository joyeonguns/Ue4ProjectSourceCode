// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsinAttackRange.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "TPS_Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsinAttackRange::UBTDecorator_IsinAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsinAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!ControllingPawn) false;

	auto Target = Cast<ATPS_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemy_AIController::TargetKey));
	auto Enemy = Cast<AEnemyBasic_Character>(OwnerComp.GetAIOwner()->GetPawn());

	if (Target == nullptr) return false;

	if (!Enemy) return false;

	float AttackRange = Enemy->GetAttackRange();

	bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRange);

	return bResult;
}
