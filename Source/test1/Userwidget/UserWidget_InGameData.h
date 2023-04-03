// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/CanvasPanel.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Components/Button.h>
#include "UserWidget_InGameData.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnExitInGameDataWidget_Delecate);

UCLASS()
class TEST1_API UUserWidget_InGameData : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;


	void DefaultUISetting();

	FOnExitInGameDataWidget_Delecate OnExitInGameDataWidget;

	UFUNCTION()
		void OnClickExitBTN();
	UFUNCTION()
		void OnClickNextPage();

	UFUNCTION()
		void Set_StageNumber();
	UFUNCTION()
		void Set_EnemyData();
	UFUNCTION()
		void Set_PlayerData();


private:
	UPROPERTY()
		class UButton* Btn_Exit;
	UPROPERTY()
		class UButton* Btn_NextPage;
	UPROPERTY()
		class UButton* Btn_PrePage;

	UPROPERTY()
		class UTextBlock* Text_StageNumber;
	UPROPERTY()
		class UTextBlock* Text_EnenyData;
	UPROPERTY()
		class UTextBlock* Text_PlayerData;

	UPROPERTY()
		class UCanvasPanel* Page_1;
	UPROPERTY()
		class UCanvasPanel* Page_2;

	UPROPERTY()
		TArray<class UCanvasPanel*> Pages;

	int32 CurrentPage = 1;
	const int32 MaxPage = 2;

};
