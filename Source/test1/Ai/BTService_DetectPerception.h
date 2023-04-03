// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectPerception.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UBTService_DetectPerception : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_DetectPerception();


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory, float DeltaTime);


private:


};
