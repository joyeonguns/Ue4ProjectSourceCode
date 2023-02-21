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
	FCharacterStat() : Role("None"), Hp(0), Str(0), Agi(0), Int(0) {};
	UPROPERTY(EditAnywhere, Category = "Data")
		FString Role;
	UPROPERTY(EditAnywhere, Category = "Data")
		float Hp;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Str;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Agi;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Int;
};

UCLASS()
class TEST1_API UCharacterStat_DataTable : public UDataTable
{
	GENERATED_BODY()
	

};
