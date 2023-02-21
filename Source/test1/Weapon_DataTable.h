// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Weapon_DataTable.generated.h"

/**
 * 
 */

//USTRUCT(BlueprintType)
//struct FWeaponData : public FTableRowBase
//{
//	GENERATED_BODY()
//
//public:
//	FWeaponData() : Weapon_Name("None"), Damage(0), Speed(5), Range(0) {};
//	UPROPERTY(EditAnywhere, Category = "Data")
//		FString Weapon_Name;
//	UPROPERTY(EditAnywhere, Category = "Data")
//		float Damage;
//	UPROPERTY(EditAnywhere, Category = "Data")
//		int32 Speed;
//	UPROPERTY(EditAnywhere, Category = "Data")
//		int32 Range;
//
//
//};

UCLASS()
class TEST1_API UWeapon_DataTable : public UDataTable
{
	GENERATED_BODY()
	
};
