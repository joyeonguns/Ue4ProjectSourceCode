// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStat_DataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterStat() : School("None"), Hp(0), Damage(0), Critical(0), CoolTime(0), percentage(7) {};
	UPROPERTY(EditAnywhere, Category = "Data")
		FString School;
	UPROPERTY(EditAnywhere, Category = "Data")
		float Hp;
	UPROPERTY(EditAnywhere, Category = "Data")
		float Damage;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Critical;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 CoolTime;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 percentage;

	void DeepCopy(FCharacterStat* newStat) {
		newStat->School = this->School;
		newStat->Hp = this->Hp;
		newStat->Damage = this->Damage;
		newStat->Critical = this->Critical;
		newStat->CoolTime = this->CoolTime;
		newStat->percentage = this->percentage;
	}
};

USTRUCT(BlueprintType)
struct FStageDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStageDataTable() : Stage(0), Range(0), Melee(0), Boss(0) {};

	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Stage;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Range;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Melee;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Boss;

};

UCLASS()
class TEST1_API UCharacterStat_DataTable : public UDataTable
{
	GENERATED_BODY()
	

};
