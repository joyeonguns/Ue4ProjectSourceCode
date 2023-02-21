// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_GameState.h"

ATPS_GameState::ATPS_GameState()
{
	MaxEnemyCount = 2;
	currentEnemyCount = 2;

	MaxHp = 80;
	currentHp = 80;

	ItemCode_0 = 0;
	ItemCode_1 = 0;

	MaxUltiGage = 100;
	currentUltiGage = 50;
}

void ATPS_GameState::IninGameDate()
{
	MaxUltiGage = 100;
	currentUltiGage = 80;
}
