// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckAttackRange.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "TPS_Character.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckAttackRange::UBTService_CheckAttackRange()
{
	NodeName = TEXT("CheckAttackRange");
	Interval = 1.0f;
}

void UBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaTime);

	bool bResult = false;

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!ControllingPawn) false;

	auto Target = Cast<ATPS_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemy_AIController::TargetKey));
	auto Enemy = Cast<AEnemyBasic_Character>(OwnerComp.GetAIOwner()->GetPawn());

	if (Target == nullptr) return;

	if (Enemy == nullptr) return;

	float AttackRange = Enemy->GetAttackRange();

	bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRange);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemy_AIController::bCanAttackKey, bResult);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BTService_CheckAttackRange::TickNode  "));
}
