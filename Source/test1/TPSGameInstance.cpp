// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameInstance.h"

UTPSGameInstance::UTPSGameInstance()
{
	// 무기
	FString WeaponData_Path = TEXT("CompositeDataTable'/Game/Data/Weapons_DataTable.Weapons_DataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Weapon(*WeaponData_Path);

	if (DT_Weapon.Succeeded()) {
		WeaponTable = DT_Weapon.Object;
		/*if (WeaponTable->GetRowMap().Num() > 0) {
			WeaponTable = DT_Weapon.Object;

		}*/
	}

	// 스테이지 데이터
	FString Stage_Data_Path = TEXT("DataTable'/Game/Data/StageData.StageData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Stage(*Stage_Data_Path);

	if (DT_Stage.Succeeded()) {
		StageDataTable = DT_Stage.Object;
	}


	// 플레이어 데이터
	FString CharStat_Data_Path = TEXT("DataTable'/Game/Data/Character_Status.Character_Status'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Char_stat(*CharStat_Data_Path);

	if (DT_Char_stat.Succeeded()) {
		Character_stat_Table = DT_Char_stat.Object;
	}
	
	// 스텟 레벨
	FString StatusLevel_Path = TEXT("DataTable'/Game/Data/StatusLevel.StatusLevel'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_StatLevel(*StatusLevel_Path);

	if (DT_StatLevel.Succeeded()) {
		StatusLevelTable = DT_StatLevel.Object;
	}

	// 원거리적 데이터
	FString RangeStat_Data_Path = TEXT("DataTable'/Game/Data/EnemyRangeLevel.EnemyRangeLevel'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Range_stat(*RangeStat_Data_Path);

	if (DT_Range_stat.Succeeded()) {
		EnemyRange_stat_Table = DT_Range_stat.Object;
	}

	// 근거리적 데이터
	FString MeleeStat_Data_Path = TEXT("DataTable'/Game/Data/EnemyMeleeLevel.EnemyMeleeLevel'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Melee_stat(*MeleeStat_Data_Path);

	if (DT_Melee_stat.Succeeded()) {
		EnemyMelee_stat_Table = DT_Melee_stat.Object;
	}

	statusArray.Init(6,8);

	for (int i = 0; i < 3; i++) {
		UnLockItemList.Add(0);
	}	

	for (int i = 0; i < 12; i++) {
		LockItemList.Add(0);
	}
}

void UTPSGameInstance::Init()
{
	Super::Init();

	BattleData_Enemy = new FBattleData_Enemy();
	BattleData_Player = new FBattleData_Player();
	
}

FWeaponData* UTPSGameInstance::Weapons_Data(int32 code)
{
	return WeaponTable->FindRow<FWeaponData>(*FString::FromInt(code), TEXT(""));
}

FStageDataTable* UTPSGameInstance::Get_FStageDataTable(int32 level)
{
	return StageDataTable->FindRow<FStageDataTable>(*FString::FromInt(level), TEXT(""));
}

FStatusLevel* UTPSGameInstance::Get_FStatusLevel(int32 level)
{
	return StatusLevelTable->FindRow<FStatusLevel>(*FString::FromInt(level), TEXT(""));
}

FCharacterStat* UTPSGameInstance::Get_FCharacter_Status(int32 code)
{
	return Character_stat_Table->FindRow<FCharacterStat>(*FString::FromInt(code), TEXT(""));
}

FCharacterStat* UTPSGameInstance::Get_FEnemyRange_Status(int32 code)
{
	return EnemyRange_stat_Table->FindRow<FCharacterStat>(*FString::FromInt(code), TEXT(""));
}

FCharacterStat* UTPSGameInstance::Get_FEnemyMelee_Status(int32 code)
{
	return EnemyMelee_stat_Table->FindRow<FCharacterStat>(*FString::FromInt(code), TEXT(""));
}

FBattleData_Enemy* UTPSGameInstance::Get_BattleData_Enemy()
{
	return BattleData_Enemy;
}

FBattleData_Player* UTPSGameInstance::Get_BattleData_Player()
{
	return BattleData_Player;
}
