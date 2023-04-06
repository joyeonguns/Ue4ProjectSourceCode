// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/CanvasPanel.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Components/Button.h>
#include "Looby_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ULooby_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	// 상단 버튼
		// 스테이터스 페이지 이동
	UFUNCTION()
	void OnClicked_GoStatBTN();
		// 도감 페이지 이동
	UFUNCTION()
	void OnClicked_GoDataBTN();
		// 속성 선택 페이지 이동
	UFUNCTION()
	void OnClicked_GoInGameBTN();
		// 타이틀로 이동
	UFUNCTION()
	void OnClicked_GoTitleBTN();


	//  StatusPage	
		// + - 기능
	void AddStatus(int32 num);
	void DesStatus(int32 num);
		// 능력 업그레이드 + - 버튼
	UFUNCTION()
		void OnClicked_AddStatBTN_0();
	UFUNCTION()
		void OnClicked_DesStatBTN_0();

	UFUNCTION()
		void OnClicked_AddStatBTN_1();
	UFUNCTION()
		void OnClicked_DesStatBTN_1();

	UFUNCTION()
		void OnClicked_AddStatBTN_2();
	UFUNCTION()
		void OnClicked_DesStatBTN_2();

	UFUNCTION()
		void OnClicked_AddStatBTN_3();
	UFUNCTION()
		void OnClicked_DesStatBTN_3();

	UFUNCTION()
		void OnClicked_AddStatBTN_4();
	UFUNCTION()
		void OnClicked_DesStatBTN_4();

	UFUNCTION()
		void OnClicked_AddStatBTN_5();
	UFUNCTION()
		void OnClicked_DesStatBTN_5();

	


	// InGamePage
	UFUNCTION()
		void OnClicked_GameStart();

	// 특성 선택
	UFUNCTION()
		void OnClicked_SelectSchool_1();
	UFUNCTION()
		void OnClicked_SelectSchool_2();
	UFUNCTION()
		void OnClicked_SelectSchool_3();


	// 능력치 업그레이드 텍스트 설정
	void SetStatState();
	// GameInstance에서 능력치 업그레이드 배열 가져옴
	void TakeStatusArray();

private:
	// 능력치 업그레이드 배열 
	TArray<int32> statusArray;
	// 특성 코드
	int32 SelectSchool;


	// Canvas
	UPROPERTY()
		class UCanvasPanel* StatPanel;
	UPROPERTY()
		class UCanvasPanel* WeaponPanel;
	UPROPERTY()
		class UCanvasPanel* InGamePanel;


	// highBar Button
	UPROPERTY()
		class UButton* BTN_GoStat;
	UPROPERTY()
		class UButton* BTN_GoWeapon;
	UPROPERTY()
		class UButton* BTN_GoInGame;
	UPROPERTY()
		class UButton* BTN_GoTitle;


	// StatPage
	// 능력 업그레이드 + 버튼 배열 
	TArray<class UButton*> AddButtonArray;
	// 능력 업그레이드 - 버튼 배열 
	TArray<class UButton*> DesButtonArray;
	// 능력 업그레이드 수치 Text 배열 
	TArray<class UTextBlock*> StatNumArray;
	// 능력 업그레이드 설명 Text 배열 
	TArray<class UTextBlock*> StatCommentArray;

	UPROPERTY()
		class UButton* BTN_AddStat_0;
	UPROPERTY()
		class UButton* BTN_DesStat_0;
	UPROPERTY()
		class UTextBlock* Text_NumStat_0;
	UPROPERTY()
		class UTextBlock* Text_StatComent_0;

	UPROPERTY()
		class UButton* BTN_AddStat_1;
	UPROPERTY()
		class UButton* BTN_DesStat_1;
	UPROPERTY()
		class UTextBlock* Text_NumStat_1;
	UPROPERTY()
		class UTextBlock* Text_StatComent_1;

	UPROPERTY()
		class UButton* BTN_AddStat_2;
	UPROPERTY()
		class UButton* BTN_DesStat_2;
	UPROPERTY()
		class UTextBlock* Text_NumStat_2;
	UPROPERTY()
		class UTextBlock* Text_StatComent_2;

	UPROPERTY()
		class UButton* BTN_AddStat_3;
	UPROPERTY()
		class UButton* BTN_DesStat_3;
	UPROPERTY()
		class UTextBlock* Text_NumStat_3;
	UPROPERTY()
		class UTextBlock* Text_StatComent_3;

	UPROPERTY()
		class UButton* BTN_AddStat_4;
	UPROPERTY()
		class UButton* BTN_DesStat_4;
	UPROPERTY()
		class UTextBlock* Text_NumStat_4;
	UPROPERTY()
		class UTextBlock* Text_StatComent_4;

	UPROPERTY()
		class UButton* BTN_AddStat_5;
	UPROPERTY()
		class UButton* BTN_DesStat_5;
	UPROPERTY()
		class UTextBlock* Text_NumStat_5;
	UPROPERTY()
		class UTextBlock* Text_StatComent_5;

	// 포인트 텍스트
	UPROPERTY()
		class UTextBlock* poinText;
	int32 point;



	// InGame 버튼
	UPROPERTY()
		class UButton* BTN_GameStart;
	UPROPERTY()
		class UButton* BTN_SelectWeapon_0;
	UPROPERTY()
		class UButton* BTN_SelectWeapon_1;
	UPROPERTY()
		class UButton* BTN_SelectWeapon_2;

};
