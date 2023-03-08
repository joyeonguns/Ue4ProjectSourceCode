// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTable_Status.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FStatusSkill : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStatusSkill(){};
	UPROPERTY(EditAnywhere, Category = "Stat")
		int status_0;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int status_1;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int status_2;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int status_3;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int status_4;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int status_5;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int status_6;
	UPROPERTY(EditAnywhere, Category = "Stat")
		int status_7;
};


UCLASS()
class TEST1_API UDataTable_Status : public UDataTable
{
	GENERATED_BODY()
	
};
