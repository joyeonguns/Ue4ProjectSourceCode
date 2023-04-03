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
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;

	void SetHP(float _currentHp, float _MaxHp);

	void SetEnemyCount(int32 _currentEnemy, int32 _MaxEnemy);

	void SetItem_0(int32 _itemCode);
	void SetItem_1(int32 _itemCode);

	void SetUlti(float _currentUlti, float _MaxUlti);

	void SetProgressBar_Skill_Q(float percent, float currentCoolTime);
	void SetProgressBar_Skill_E(float percent, float currentCoolTime);
	void SetProgressBar_Item_1(float percent, float currentCoolTime);
	void SetProgressBar_Item_2(float percent, float currentCoolTime);

	void SetTakeDamage(float _Damage);
	void SetTakeDamage();

	void SetItemCount_1(int32 count);
	void SetItemCount_2(int32 count);

	void SetPoint(float _point);
	void SetGetPoint(float _getPoint);
	void SetGetPoint();

private:

	int32 MaxEnemyCount;
	int32 currentEnemyCount;

	float MaxHp;
	float currentHp;

	int32 ItemCode_0;
	int32 ItemCode_1;

	float MaxUltiGage;
	float currentUltiGage;

	float TakeDamageLifeTime;
	bool bTakeDamage;

	float GetPointLifeTime;
	bool bGetPoint;

	UPROPERTY()
		class UTextBlock* EnemyState_Text;

	UPROPERTY()
		class UProgressBar* HP_ProgressBar;

	UPROPERTY()
		class UImage* Weapon_Img;

	UPROPERTY()
		class UProgressBar* ProgressBar_Skill_Q;
	UPROPERTY()
		class UProgressBar* ProgressBar_Skill_E;

	UPROPERTY()
		class UProgressBar* ProgressBar_Item_1;
	UPROPERTY()
		class UProgressBar* ProgressBar_Item_2;

	UPROPERTY()
		class UTextBlock* Text_CoolTime_Q;

	UPROPERTY()
		class UTextBlock* Text_CoolTime_E;

	UPROPERTY()
		class UTextBlock* Text_CoolTime_1;

	UPROPERTY()
		class UTextBlock* Text_CoolTime_2;

	UPROPERTY()
		class UTextBlock* Text_Count_1;

	UPROPERTY()
		class UTextBlock* Text_Count_2;
	
	
	UPROPERTY()
		class UTextBlock* Text_TakeDamage;

	UPROPERTY()
		class UTextBlock* Text_Point;
	UPROPERTY()
		class UTextBlock* Text_GetPoint;



};
