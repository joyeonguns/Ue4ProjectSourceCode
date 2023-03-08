// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameInstance.h"

UTPSGameInstance::UTPSGameInstance()
{
	FString WeaponData_Path = TEXT("CompositeDataTable'/Game/Data/Weapons_DataTable.Weapons_DataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Weapon(*WeaponData_Path);

	if (DT_Weapon.Succeeded()) {
		WeaponTable = DT_Weapon.Object;
		/*if (WeaponTable->GetRowMap().Num() > 0) {
			WeaponTable = DT_Weapon.Object;

		}*/
	}

	FString CharStat_Data_Path = TEXT("DataTable'/Game/Data/Character_Stat.Character_Stat'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Char_stat(*CharStat_Data_Path);

	if (DT_Char_stat.Succeeded()) {
		Character_stat_Table = DT_Char_stat.Object;
		/*if (WeaponTable->GetRowMap().Num() > 0) {
			WeaponTable = DT_Weapon.Object;

		}*/
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

	/*FWeaponData* WD = Weapons_Data(2);

	UE_LOG(LogTemp, Log, TEXT("Log:: Inin"));

	if (WD) {
		UE_LOG(LogTemp, Warning, TEXT("Sword's Damage : %f"), WD->Damage);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT(" ERROR "));
	}*/
	
}

FWeaponData* UTPSGameInstance::Weapons_Data(int32 code)
{
	return WeaponTable->FindRow<FWeaponData>(*FString::FromInt(code), TEXT(""));
}

FCharacterStat* UTPSGameInstance::Get_FCharacter_Status(int32 code)
{
	return Character_stat_Table->FindRow<FCharacterStat>(*FString::FromInt(code), TEXT(""));
}
