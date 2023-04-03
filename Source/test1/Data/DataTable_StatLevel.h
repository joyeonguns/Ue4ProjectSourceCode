// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTable_StatLevel.generated.h"

USTRUCT(BlueprintType)
struct FStatusLevel : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStatusLevel() : Hp(0), Damage(0), Critical(0), CoolTime(0) {};
	UPROPERTY(EditAnywhere, Category = "Data")
		float Hp;
	UPROPERTY(EditAnywhere, Category = "Data")
		float Damage;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 Critical;
	UPROPERTY(EditAnywhere, Category = "Data")
		int32 CoolTime;
};

/**
 * 
 */
UCLASS()
class TEST1_API UDataTable_StatLevel : public UDataTable
{
	GENERATED_BODY()
	
};
