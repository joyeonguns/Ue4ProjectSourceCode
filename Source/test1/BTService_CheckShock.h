// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckShock.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UBTService_CheckShock : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_CheckShock();


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime);

};
