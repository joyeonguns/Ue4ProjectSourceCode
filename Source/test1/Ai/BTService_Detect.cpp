// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "Enemy_AIController.h"
#include "EnemyBasic_Character.h"
#include "TPS_Character.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickNode(OwerComp, NodeMemory, DeltaTime);

	APawn* ControllingPawn = OwerComp.GetAIOwner()->GetPawn();

	if (!ControllingPawn)
		return;

	UWorld* world = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetecteRadius = 600.0f;

	if (!world) return;

	// FOverlapResult 를 통해 타겟 감지 360도 감지
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = world->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetecteRadius),
		CollisionQueryParam
	);

	if (bResult) {
		for (auto const& OverlapResult : OverlapResults) {
			ATPS_Character* player = Cast<ATPS_Character>(OverlapResult.GetActor());
			if (player && player->GetController()->IsPlayerController()) {
				OwerComp.GetBlackboardComponent()->SetValueAsObject(AEnemy_AIController::TargetKey, player);
				DrawDebugSphere(world, Center, DetecteRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugLine(world, ControllingPawn->GetActorLocation(), player->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}

	DrawDebugSphere(world, Center, DetecteRadius, 16, FColor::Red, false, 0.2f);


}
