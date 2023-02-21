// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrollPos.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UBTTask_FindPatrollPos : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_FindPatrollPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


private:


};
