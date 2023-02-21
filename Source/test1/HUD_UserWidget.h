// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "HUD_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UHUD_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetHP(float _currentHp, float _MaxHp);

	void SetEnemyCount(int32 _currentEnemy, int32 _MaxEnemy);

	void SetItem_0(int32 _itemCode);
	void SetItem_1(int32 _itemCode);

	void SetUlti(float _currentUlti, float _MaxUlti);


private:

	int32 MaxEnemyCount;
	int32 currentEnemyCount;

	float MaxHp;
	float currentHp;

	int32 ItemCode_0;
	int32 ItemCode_1;

	float MaxUltiGage;
	float currentUltiGage;

	UPROPERTY()
		class UTextBlock* EnemyState_Text;

	UPROPERTY()
		class UProgressBar* HP_ProgressBar;

	UPROPERTY()
		class UImage* Weapon_Img;
	UPROPERTY()
		class UImage* Item_Image0;
	UPROPERTY()
		class UImage* Item_Image1;

	UPROPERTY()
		class UProgressBar* Ulti_ProgressBar;
	UPROPERTY()
		class UImage* UltiHighlight_Image;


};
