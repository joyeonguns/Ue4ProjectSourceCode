// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectPerception.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "TPS_Character.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_DetectPerception::UBTService_DetectPerception()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_DetectPerception::TickNode(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickNode(OwerComp, NodeMemory, DeltaTime);

	APawn* ControllingPawn = OwerComp.GetAIOwner()->GetPawn();

	if (!ControllingPawn)
		return;

	AEnemy_AIController* aicontroller = Cast<AEnemy_AIController>(OwerComp.GetAIOwner());

	if (aicontroller) {
		ATPS_Character* player = aicontroller->GetPlayer();
		
		auto pl = OwerComp.GetBlackboardComponent()->GetValueAsObject("Target");

		if (!pl && player) {
			OwerComp.GetBlackboardComponent()->SetValueAsObject(AEnemy_AIController::TargetKey, player);
			OwerComp.GetBlackboardComponent()->SetValueAsVector(AEnemy_AIController::TargetPosKey, player->GetActorLocation());
		}
	}

}