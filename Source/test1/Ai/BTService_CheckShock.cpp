// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckShock.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "TPS_Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_CheckShock::UBTService_CheckShock()
{
	NodeName = TEXT("CheckShock");
	Interval = 0.5f;
}

void UBTService_CheckShock::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaTime);

	bool bResult;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!ControllingPawn)
		return;

	auto Target = Cast<ATPS_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemy_AIController::TargetKey));
	auto Enemy = Cast<AEnemyBasic_Character>(OwnerComp.GetAIOwner()->GetPawn());


	// 충격 상태 체크
	bResult = (Enemy->GetCheckShocking());

	// bShockKey 값 업데이트
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemy_AIController::bShockKey, bResult);

	if (bResult) {
		auto pl = Cast<ATPS_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemy_AIController::TargetKey, pl);
	}
}
