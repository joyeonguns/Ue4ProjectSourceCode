// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "CharacterStat_DataTable.h"
#include "DataTable_Status.h"
#include "TPSGameInstance.generated.h"

/**
 * 
 */

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

	// ���� ���� �ʱ�ȭ �ɽ� ȣ��Ǵ� �Լ�
	virtual void Init() override;

	FWeaponData* Weapons_Data(int32 code);

	UPROPERTY()
		class UDataTable* WeaponTable;

	FCharacterStat* Get_FCharacter_Status(int32 code);

	UPROPERTY()
		class UDataTable* Character_stat_Table;

	UPROPERTY(VisibleAnywhere, Category = Status)
		TArray<int32> statusArray;

	UPROPERTY(VisibleAnywhere, Category = Item)
		TArray<int32> UnLockItemList;

	UPROPERTY(VisibleAnywhere, Category = Item)
		TArray<int32> LockItemList;

	UPROPERTY(VisibleAnywhere, Category = Item)
		int32 SelectedWeaponCode = 0;

};
