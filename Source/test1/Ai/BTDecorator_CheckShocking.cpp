// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckShocking.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "TPS_Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckShocking::UBTDecorator_CheckShocking()
{
	NodeName = TEXT("CheckShocking");
	
}

bool UBTDecorator_CheckShocking::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!ControllingPawn) false;

	auto Enemy = Cast<AEnemyBasic_Character>(ControllingPawn);

	if (Enemy == nullptr) return false;

	bResult = (Enemy->GetCheckShocking());


	return bResult;
}

