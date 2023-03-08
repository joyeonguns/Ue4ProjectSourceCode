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

	// HightBar
	UFUNCTION()
	void OnClicked_GoStatBTN();
	UFUNCTION()
	void OnClicked_GoWeaponBTN();
	UFUNCTION()
	void OnClicked_GoInGameBTN();
	UFUNCTION()
	void OnClicked_GoTitleBTN();


	//  StatusPage
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

	UFUNCTION()
		void OnClicked_AddStatBTN_6();
	UFUNCTION()
		void OnClicked_DesStatBTN_6();

	UFUNCTION()
		void OnClicked_AddStatBTN_7();
	UFUNCTION()
		void OnClicked_DesStatBTN_7();


	// InGamePage
	UFUNCTION()
		void OnClicked_GameStart();

	UFUNCTION()
		void OnClicked_SelectWeapon_0();
	UFUNCTION()
		void OnClicked_SelectWeapon_1();
	UFUNCTION()
		void OnClicked_SelectWeapon_2();



	void SetStatState();
	void TakeStatusArray();
private:
	TArray<int32> statusArray;
	TArray<int32> UnLockArray;
	int32 SelectWeaponCode;
	FLinearColor inactiveColor;
	FLinearColor activeColor;

	TArray<UImage*> WeaponBook;

	// Canvas
	UPROPERTY()
		class UCanvasPanel* StatPanel;
	UPROPERTY()
		class UCanvasPanel* WeaponPanel;
	UPROPERTY()
		class UCanvasPanel* InGamePanel;


	// highBar
	UPROPERTY()
		class UButton* BTN_GoStat;
	UPROPERTY()
		class UButton* BTN_GoWeapon;
	UPROPERTY()
		class UButton* BTN_GoInGame;
	UPROPERTY()
		class UButton* BTN_GoTitle;

	// StatPage
	UPROPERTY()
		class UButton* BTN_AddStat_0;
	UPROPERTY()
		class UButton* BTN_DecStat_0;
	UPROPERTY()
		class UTextBlock* Text_NumStat_0;

	UPROPERTY()
		class UButton* BTN_AddStat_1;
	UPROPERTY()
		class UButton* BTN_DecStat_1;
	UPROPERTY()
		class UTextBlock* Text_NumStat_1;

	UPROPERTY()
		class UButton* BTN_AddStat_2;
	UPROPERTY()
		class UButton* BTN_DecStat_2;
	UPROPERTY()
		class UTextBlock* Text_NumStat_2;

	UPROPERTY()
		class UButton* BTN_AddStat_3;
	UPROPERTY()
		class UButton* BTN_DecStat_3;
	UPROPERTY()
		class UTextBlock* Text_NumStat_3;

	UPROPERTY()
		class UButton* BTN_AddStat_4;
	UPROPERTY()
		class UButton* BTN_DecStat_4;
	UPROPERTY()
		class UTextBlock* Text_NumStat_4;

	UPROPERTY()
		class UButton* BTN_AddStat_5;
	UPROPERTY()
		class UButton* BTN_DecStat_5;
	UPROPERTY()
		class UTextBlock* Text_NumStat_5;

	UPROPERTY()
		class UButton* BTN_AddStat_6;
	UPROPERTY()
		class UButton* BTN_DecStat_6;
	UPROPERTY()
		class UTextBlock* Text_NumStat_6;

	UPROPERTY()
		class UButton* BTN_AddStat_7;
	UPROPERTY()
		class UButton* BTN_DecStat_7;
	UPROPERTY()
		class UTextBlock* Text_NumStat_7;

	UPROPERTY()
		class UTextBlock* poinText;
	int32 point;


	// WeaponBook
	UPROPERTY()
		class UImage* Img_Weapon_0;
	UPROPERTY()
		class UImage* Img_Weapon_1;
	UPROPERTY()
		class UImage* Img_Weapon_2;
	UPROPERTY()
		class UImage* Img_Weapon_3;
	UPROPERTY()
		class UImage* Img_Weapon_4;
	UPROPERTY()
		class UImage* Img_Weapon_5;
	UPROPERTY()
		class UImage* Img_Weapon_6;
	UPROPERTY()
		class UImage* Img_Weapon_7;
	UPROPERTY()
		class UImage* Img_Weapon_8;
	UPROPERTY()
		class UImage* Img_Weapon_9;
	UPROPERTY()
		class UImage* Img_Weapon_10;
	UPROPERTY()
		class UImage* Img_Weapon_11;
	UPROPERTY()
		class UImage* Img_Weapon_12;
	UPROPERTY()
		class UImage* Img_Weapon_13;
	UPROPERTY()
		class UImage* Img_Weapon_14;




	// InGame
	UPROPERTY()
		class UButton* BTN_GameStart;
	UPROPERTY()
		class UButton* BTN_SelectWeapon_0;
	UPROPERTY()
		class UButton* BTN_SelectWeapon_1;
	UPROPERTY()
		class UButton* BTN_SelectWeapon_2;

};
