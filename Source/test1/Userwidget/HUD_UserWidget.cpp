// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_UserWidget.h"

void UHUD_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
 

	// HP bar
	HP_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));

	// 스킬 및 아이템
	ProgressBar_Item_1 = Cast<UProgressBar>(GetWidgetFromName(TEXT("bar_Item_1")));
	ProgressBar_Item_2 = Cast<UProgressBar>(GetWidgetFromName(TEXT("bar_Item_2")));

	ProgressBar_Skill_Q = Cast<UProgressBar>(GetWidgetFromName(TEXT("Skill_Image_0")));
	ProgressBar_Skill_E = Cast<UProgressBar>(GetWidgetFromName(TEXT("Skill_Image_1")));

	Text_CoolTime_Q = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_CoolTime_Q")));
	Text_CoolTime_E = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_CoolTime_E")));
	Text_CoolTime_1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_CoolTime_1")));
	Text_CoolTime_2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_CoolTime_2")));

	Text_Count_1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Count_1")));
	Text_Count_2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Count_2")));

	// 받은 데미지
	Text_TakeDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_TakeDamage")));
	// 현재 포인트
	Text_Point = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Point")));
	// 획득 포인트
	Text_GetPoint = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_GetPoint")));

}

void UHUD_UserWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

	// 데미지 프린팅
	if (bTakeDamage) {
		TakeDamageLifeTime -= DeltaSeconds;
		if (TakeDamageLifeTime <= 0.0f) {
			// 지속시간 끝나면 제거
			SetTakeDamage();
		}
	}

	// 획득 포인트 프린팅
	if (bGetPoint) {
		GetPointLifeTime -= DeltaSeconds;
		if (GetPointLifeTime <= 0.0f) {
			// 지속시간 끝나면 제거
			SetGetPoint();
		}
	}
	
}

void UHUD_UserWidget::SetHP(float _currentHp, float _MaxHp)
{
	// Hp 퍼센트 계산
	float percent = _currentHp / _MaxHp;

	if (percent <= 0.0f) {
		percent = 0.0f;
	}
	else if (percent >= 1.0f) {
		percent = 1.0f;
	}

	// HP bar 적용
	HP_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));
	if (HP_ProgressBar) {
		HP_ProgressBar->SetPercent(percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("HP_ProgressBar not find"));
	}
}

void UHUD_UserWidget::SetProgressBar_Skill_Q(float percent, float currentCoolTime)
{
	// 퍼센트 계산
	// 프로그래스바가 사라지는 연출을 위해 1 - 쿨다운퍼센트 해준다.
	float _percent = 1 - percent;;

	if (_percent <= 0.0f) {
		_percent = 0.0f;
	}
	else if (_percent >= 1.0f) {
		_percent = 1.0f;
	}

	// 스킬 쿨타임 적용
		// 쿨타임인 경우 수치를 표기
	if (_percent > 0.0f) {
		float cooltime = floor(currentCoolTime * 10) / 10;
		Text_CoolTime_Q->SetText(FText::AsNumber(cooltime));
	}
		// 쿨타임이 아닌경우 수치 제거
	else {
		Text_CoolTime_Q->SetText(FText::FromString(TEXT("")));
	}

	// 프로그래스바 설정
	if (ProgressBar_Skill_Q) {
		ProgressBar_Skill_Q->SetPercent(_percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ProgressBar_Skill_Q"));
	}
}

void UHUD_UserWidget::SetProgressBar_Skill_E(float percent, float currentCoolTime)
{
	// 퍼센트 계산
	// 프로그래스바가 사라지는 연출을 위해 1 - 쿨다운퍼센트 해준다.
	float _percent = 1 - percent;;

	if (_percent <= 0.0f) {
		_percent = 0.0f;
	}
	else if (_percent >= 1.0f) {
		_percent = 1.0f;
	}

	// 스킬 쿨타임 적용
		// 쿨타임인 경우 수치를 표기
	if (_percent > 0.0f) {
		float cooltime = floor(currentCoolTime * 10) / 10;
		Text_CoolTime_E->SetText(FText::AsNumber(cooltime));
	}
		// 쿨타임이 아닌경우 수치 제거
	else {
		Text_CoolTime_E->SetText(FText::FromString(TEXT("")));
	}

	// 프로그래스바 설정
	if (ProgressBar_Skill_E) {
		ProgressBar_Skill_E->SetPercent(_percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ProgressBar_Skill_E"));
	}
}

void UHUD_UserWidget::SetProgressBar_Item_1(float percent, float currentCoolTime)
{
	// 퍼센트 계산
	// 프로그래스바가 사라지는 연출을 위해 1 - 쿨다운퍼센트 해준다.
	float _percent = 1 - percent;

	if (_percent <= 0.0f) {
		_percent = 0.0f;
	}
	else if (_percent >= 1.0f) {
		_percent = 1.0f;
	}

	// 스킬 쿨타임 적용
		// 쿨타임인 경우 수치를 표기
	if (_percent > 0.0f) {
		float cooltime = floor(currentCoolTime * 10) / 10;
		Text_CoolTime_1->SetText(FText::AsNumber(cooltime));
	}
		// 쿨타임이 아닌경우 수치 제거
	else {
		Text_CoolTime_1->SetText(FText::FromString(TEXT("")));
	}

	// 프로그래스바 설정
	if (ProgressBar_Item_1) {
		ProgressBar_Item_1->SetPercent(_percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ProgressBar_Item_1"));
	}
}

void UHUD_UserWidget::SetProgressBar_Item_2(float percent, float currentCoolTime)
{
	// 퍼센트 계산
	// 프로그래스바가 사라지는 연출을 위해 1 - 쿨다운퍼센트 해준다.
	float _percent = 1 - percent;;

	if (_percent <= 0.0f) {
		_percent = 0.0f;
	}
	else if (_percent >= 1.0f) {
		_percent = 1.0f;
	}

	// 스킬 쿨타임 적용
		// 쿨타임인 경우 수치를 표기
	if (_percent > 0.0f) {
		float cooltime = floor(currentCoolTime * 10) / 10;
		Text_CoolTime_2->SetText(FText::AsNumber(cooltime));
	}
		// 쿨타임이 아닌경우 수치 제거
	else {
		Text_CoolTime_2->SetText(FText::FromString(TEXT("")));
	}

	// 프로그래스바 설정
	if (ProgressBar_Item_2) {
		ProgressBar_Item_2->SetPercent(_percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ProgressBar_Item_2"));
	}
}

void UHUD_UserWidget::SetTakeDamage(float _Damage)
{
	// 데미지 프린트
	FString output = "-" + FString::FormatAsNumber(_Damage);
	Text_TakeDamage->SetText(FText::FromString(output));

	// 지속시간 상태 설정
	TakeDamageLifeTime = 2.0f;
	bTakeDamage = true;
}

void UHUD_UserWidget::SetTakeDamage()
{
	// 데미지 프린트 해제
	FString output = "";
	Text_TakeDamage->SetText(FText::FromString(output));

	TakeDamageLifeTime = 0.0f;
	bTakeDamage = false;
}

void UHUD_UserWidget::SetItemCount_1(int32 count)
{
	if (Text_Count_1) {
		Text_Count_1->SetText(FText::AsNumber(count));
	}
}

void UHUD_UserWidget::SetItemCount_2(int32 count)
{
	if (Text_Count_2) {
		Text_Count_2->SetText(FText::AsNumber(count));
	}
}

void UHUD_UserWidget::SetPoint(float _point)
{
	if (Text_Point) {
		Text_Point->SetText(FText::AsNumber(_point));
	}
}

void UHUD_UserWidget::SetGetPoint(float _getPoint)
{
	if (Text_GetPoint) {
		// 획득 포인트 프린트
		Text_GetPoint->SetText(FText::FromString("+" + FString::FormatAsNumber(_getPoint)));

		// 지속시간 상태 설정
		GetPointLifeTime = 2.0f;
		bGetPoint = true;
	}
}

void UHUD_UserWidget::SetGetPoint()
{
	// 획득포인트 해제
	if (Text_GetPoint) {
		Text_GetPoint->SetText(FText::FromString(""));


		GetPointLifeTime = 0.0f;
		bGetPoint = false;
	}
}

