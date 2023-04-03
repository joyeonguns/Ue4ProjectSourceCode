// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsinAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UBTDecorator_IsinAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsinAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:


};
