// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_UserWidget.h"

void UHUD_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
 
	EnemyState_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("EnemyState_TextBlock")));

	HP_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));

	Weapon_Img = Cast<UImage>(GetWidgetFromName(TEXT("Weapon_Image")));


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

	Text_TakeDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_TakeDamage")));
	
	Text_Point = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Point")));
	Text_GetPoint = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_GetPoint")));

}

void UHUD_UserWidget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

	if (bTakeDamage) {
		TakeDamageLifeTime -= DeltaSeconds;
		if (TakeDamageLifeTime <= 0.0f) {
			SetTakeDamage();
		}
	}

	if (bGetPoint) {
		GetPointLifeTime -= DeltaSeconds;
		if (GetPointLifeTime <= 0.0f) {
			SetGetPoint();
		}
	}
	
}

void UHUD_UserWidget::SetHP(float _currentHp, float _MaxHp)
{

	float percent = _currentHp / _MaxHp;

	if (percent <= 0.0f) {
		percent = 0.0f;
	}
	else if (percent >= 1.0f) {
		percent = 1.0f;
	}

	HP_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));
	if (HP_ProgressBar) {
		HP_ProgressBar->SetPercent(percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("HP_ProgressBar not find"));
	}
}

void UHUD_UserWidget::SetEnemyCount(int32 _currentEnemy, int32 _MaxEnemy)
{
	FString EnemyCount = FString::FromInt(_currentEnemy) + " / " + FString::FromInt(_MaxEnemy);
	FText EnemyText = FText::FromString(EnemyCount);

	EnemyState_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("EnemyState_TextBlock")));
	if (EnemyState_Text) {
		EnemyState_Text->SetText(EnemyText);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("EnemyState_Text not find"));
	}
}

void UHUD_UserWidget::SetItem_0(int32 _itemCode)
{
	
}

void UHUD_UserWidget::SetItem_1(int32 _itemCode)
{
}

void UHUD_UserWidget::SetUlti(float _currentUlti, float _MaxUlti)
{
	
}

void UHUD_UserWidget::SetProgressBar_Skill_Q(float percent, float currentCoolTime)
{
	float _percent = 1 - percent;;

	if (_percent <= 0.0f) {
		_percent = 0.0f;
	}
	else if (_percent >= 1.0f) {
		_percent = 1.0f;
	}

	if (_percent > 0.0f) {
		float cooltime = floor(currentCoolTime * 10) / 10;
		Text_CoolTime_Q->SetText(FText::AsNumber(cooltime));
	}
	else {
		Text_CoolTime_Q->SetText(FText::FromString(TEXT("")));
	}

	//HP_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));
	if (ProgressBar_Skill_Q) {
		ProgressBar_Skill_Q->SetPercent(_percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ProgressBar_Skill_Q"));
	}
}

void UHUD_UserWidget::SetProgressBar_Skill_E(float percent, float currentCoolTime)
{
	float _percent = 1 - percent;;

	if (_percent <= 0.0f) {
		_percent = 0.0f;
	}
	else if (_percent >= 1.0f) {
		_percent = 1.0f;
	}

	if (_percent > 0.0f) {
		float cooltime = floor(currentCoolTime * 10) / 10;
		Text_CoolTime_E->SetText(FText::AsNumber(cooltime));
	}
	else {
		Text_CoolTime_E->SetText(FText::FromString(TEXT("")));
	}

	//HP_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));
	if (ProgressBar_Skill_E) {
		ProgressBar_Skill_E->SetPercent(_percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ProgressBar_Skill_E"));
	}
}

void UHUD_UserWidget::SetProgressBar_Item_1(float percent, float currentCoolTime)
{
	float _percent = 1 - percent;

	if (_percent <= 0.0f) {
		_percent = 0.0f;
	}
	else if (_percent >= 1.0f) {
		_percent = 1.0f;
	}

	if (_percent > 0.0f) {
		float cooltime = floor(currentCoolTime * 10) / 10;
		Text_CoolTime_1->SetText(FText::AsNumber(cooltime));
	}
	else {
		Text_CoolTime_1->SetText(FText::FromString(TEXT("")));
	}

	//HP_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));
	if (ProgressBar_Item_1) {
		ProgressBar_Item_1->SetPercent(_percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ProgressBar_Item_1"));
	}
}

void UHUD_UserWidget::SetProgressBar_Item_2(float percent, float currentCoolTime)
{
	float _percent = 1 - percent;;

	if (_percent <= 0.0f) {
		_percent = 0.0f;
	}
	else if (_percent >= 1.0f) {
		_percent = 1.0f;
	}

	if (_percent > 0.0f) {
		float cooltime = floor(currentCoolTime * 10) / 10;
		Text_CoolTime_2->SetText(FText::AsNumber(cooltime));
	}
	else {
		Text_CoolTime_2->SetText(FText::FromString(TEXT("")));
	}

	//HP_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));
	if (ProgressBar_Item_2) {
		ProgressBar_Item_2->SetPercent(_percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ProgressBar_Item_2"));
	}
}

void UHUD_UserWidget::SetTakeDamage(float _Damage)
{
	FString output = "-" + FString::FormatAsNumber(_Damage);
	Text_TakeDamage->SetText(FText::FromString(output));

	TakeDamageLifeTime = 2.0f;
	bTakeDamage = true;
}

void UHUD_UserWidget::SetTakeDamage()
{
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
		Text_GetPoint->SetText(FText::FromString("+" + FString::FormatAsNumber(_getPoint)));

		GetPointLifeTime = 2.0f;
		bGetPoint = true;
	}
}

void UHUD_UserWidget::SetGetPoint()
{
	if (Text_GetPoint) {
		Text_GetPoint->SetText(FText::FromString(""));


		GetPointLifeTime = 0.0f;
		bGetPoint = false;
	}
}

