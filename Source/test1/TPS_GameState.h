// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TPS_GameState.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ATPS_GameState : public AGameState
{
	GENERATED_BODY()

public:
	ATPS_GameState();
	void IninGameDate();

private:
	int32 MaxEnemyCount;
	int32 currentEnemyCount;

	float MaxHp;
	float currentHp;

	int32 ItemCode_0;
	int32 ItemCode_1;

	float MaxUltiGage;
	float currentUltiGage;
	
};
