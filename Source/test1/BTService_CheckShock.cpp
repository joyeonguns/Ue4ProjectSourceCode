// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckShock.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "TPS_Character.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_CheckShock::UBTService_CheckShock()
{
	NodeName = TEXT("CheckShock");
}

void UBTService_CheckShock::TickNode(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickNode(OwerComp, NodeMemory, DeltaTime);

	APawn* ControllingPawn = OwerComp.GetAIOwner()->GetPawn();

	if (!ControllingPawn)
		return;
	AEnemyBasic_Character* Enemy = Cast<AEnemyBasic_Character>(ControllingPawn);

	/*if (Enemy->) {
		ATPS_Character* player = aicontroller->GetPlayer();

		if (player) {
			OwerComp.GetBlackboardComponent()->SetValueAsObject(AEnemy_AIController::TargetKey, player);
		}
	}*/
}
