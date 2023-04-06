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

	// UI 초기 설정
	void DefaultUISetting();

	// 나가기 버튼에 적용할 델리게이트함수
	FOnExitInGameDataWidget_Delecate OnExitInGameDataWidget;

	UFUNCTION()
		void OnClickExitBTN();
	UFUNCTION()
		void OnClickNextPage();

	// 현재 스테이지 텍스트 설정
	UFUNCTION()
		void Set_StageNumber();
	// 스테이지 적 데이터 텍스트 설정
	UFUNCTION()
		void Set_EnemyData();
	// 플레이어 데이터 텍스트 설정
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

	// 페이지 배열
	UPROPERTY()
		TArray<class UCanvasPanel*> Pages;

	int32 CurrentPage = 1;
	const int32 MaxPage = 2;

};
