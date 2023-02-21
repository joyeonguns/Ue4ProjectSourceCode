// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ATPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPSGameModeBase();
	virtual void StartPlay() override;
};
