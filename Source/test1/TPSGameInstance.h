// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "CharacterStat_DataTable.h"
#include "DataTable_Status.h"
#include "DataTable_StatLevel.h"
#include "TPSGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBattleData_Player
{
	GENERATED_BODY()

public:
	FBattleData_Player() : Hp(0), Damage(0), Critical(0), Speed(5), Accel_CoolTime(0), School_Percent(0) {};
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Hp;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Damage; 
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Critical;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Speed;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Accel_CoolTime;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 School_Percent;
};

USTRUCT(BlueprintType)
struct FBattleData_Enemy
{
	GENERATED_BODY()

public:
	FBattleData_Enemy() : Level(0), Elite(0), Range(0), Melee(0), Boss(0), Stage(0) {};
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Level;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Elite;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Range;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Melee;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Boss;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Stage;
};


USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FWeaponData() : Weapon_Name("None"), Damage(0), Speed(5), Range(0) {};
	UPROPERTY(EditAnywhere, Category = "Data")
		FString Weapon_Name;
	UPROPERTY(EditAnywhere, Category = "Data")
		float Damage;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Speed;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Range;
};


UCLASS()
class TEST1_API UTPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public :
	UTPSGameInstance();

	// 게임 앱이 초기화 될시 호출되는 함수
	virtual void Init() override;


	// 무기
	FWeaponData* Weapons_Data(int32 code);

	UPROPERTY()
		class UDataTable* WeaponTable;

	// 스테이지
	FStageDataTable* Get_FStageDataTable(int32 level);

	UPROPERTY()
		class UDataTable* StageDataTable;


	// 스탯 레벨
	FStatusLevel* Get_FStatusLevel(int32 level);

	UPROPERTY()
		class UDataTable* StatusLevelTable;

	// 플레이어 스텟
	FCharacterStat* Get_FCharacter_Status(int32 code);

	UPROPERTY()
		class UDataTable* Character_stat_Table;

	// 적 스텟
	FCharacterStat* Get_FEnemyRange_Status(int32 code);

	UPROPERTY()
		class UDataTable* EnemyRange_stat_Table;

	FCharacterStat* Get_FEnemyMelee_Status(int32 code);

	UPROPERTY()
		class UDataTable* EnemyMelee_stat_Table;

	// 스텟 배열
	UPROPERTY(VisibleAnywhere, Category = Status)
		TArray<int32> statusArray;

	UPROPERTY(VisibleAnywhere, Category = Item)
		TArray<int32> UnLockItemList;

	UPROPERTY(VisibleAnywhere, Category = Item)
		TArray<int32> LockItemList;

	// 속성 스텟
	UPROPERTY(VisibleAnywhere, Category = Item)
		int32 SelectedWeaponCode = 0;

	// 적 버프 확률
	UPROPERTY(VisibleAnywhere, Category = Status)
		int32 EnemyBuff = 0;

	// 포인트
	UPROPERTY(VisibleAnywhere, Category = point)
	int32 Point = 1000;


	// 전투 데이터
	FBattleData_Enemy* BattleData_Enemy;
	FBattleData_Player* BattleData_Player;

	FBattleData_Enemy* Get_BattleData_Enemy();
	FBattleData_Player* Get_BattleData_Player();
};
