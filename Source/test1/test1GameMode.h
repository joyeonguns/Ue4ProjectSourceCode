// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "test1GameMode.generated.h"

UCLASS(minimalapi)
class Atest1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	Atest1GameMode();

	virtual void StartPlay() override;
};



