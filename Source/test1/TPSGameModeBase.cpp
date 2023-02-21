// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameModeBase.h"

ATPSGameModeBase::ATPSGameModeBase()
{
}

void ATPSGameModeBase::StartPlay()
{
	Super::StartPlay();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hellow TPSGameMode"));
	}
}
