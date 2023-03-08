// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckShocking.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UBTDecorator_CheckShocking : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_CheckShocking();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
};
