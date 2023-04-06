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
	// Tick
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;

	// HPbar 적용
	void SetHP(float _currentHp, float _MaxHp);

	// 스킬 아이템 쿨타임 적용
	void SetProgressBar_Skill_Q(float percent, float currentCoolTime);
	void SetProgressBar_Skill_E(float percent, float currentCoolTime);
	void SetProgressBar_Item_1(float percent, float currentCoolTime);
	void SetProgressBar_Item_2(float percent, float currentCoolTime);

	// 받은 데미지 수치 출력 
	void SetTakeDamage(float _Damage);
	// 받은 데미지 지우기
	void SetTakeDamage();

	// 남은 아이템 개수 적용
	void SetItemCount_1(int32 count);
	void SetItemCount_2(int32 count);

	// 현재 포인트 적용
	void SetPoint(float _point);
	// 획득한 포인트 출력  
	void SetGetPoint(float _getPoint);
	// 획득한 포인트 제거 
	void SetGetPoint();

private:
	// 받은 데미지 지속시간
	float TakeDamageLifeTime;
	bool bTakeDamage;

	// 획득한 포인트 지속시간
	float GetPointLifeTime;
	bool bGetPoint;


	// HP bar
	UPROPERTY()
		class UProgressBar* HP_ProgressBar;

	// 스킬, 아이템 bar
	UPROPERTY()
		class UProgressBar* ProgressBar_Skill_Q;
	UPROPERTY()
		class UProgressBar* ProgressBar_Skill_E;

	UPROPERTY()
		class UProgressBar* ProgressBar_Item_1;
	UPROPERTY()
		class UProgressBar* ProgressBar_Item_2;

	// 스킬, 아이템 쿨타임 수치
	UPROPERTY()
		class UTextBlock* Text_CoolTime_Q;

	UPROPERTY()
		class UTextBlock* Text_CoolTime_E;

	UPROPERTY()
		class UTextBlock* Text_CoolTime_1;

	UPROPERTY()
		class UTextBlock* Text_CoolTime_2;

	// 남은 아이템 개수 
	UPROPERTY()
		class UTextBlock* Text_Count_1;

	UPROPERTY()
		class UTextBlock* Text_Count_2;
	
	// 받은데미지
	UPROPERTY()
		class UTextBlock* Text_TakeDamage;

	// 현재 포인트
	UPROPERTY()
		class UTextBlock* Text_Point;
	// 획득 포인트
	UPROPERTY()
		class UTextBlock* Text_GetPoint;



};
