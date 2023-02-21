// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_UserWidget.h"

void UHUD_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EnemyState_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("EnemyState_TextBlock")));

	HP_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));

	Weapon_Img = Cast<UImage>(GetWidgetFromName(TEXT("Weapon_Image")));

	Item_Image0 = Cast<UImage>(GetWidgetFromName(TEXT("Item_Image_0")));
	Item_Image1 = Cast<UImage>(GetWidgetFromName(TEXT("Item_Image_0")));

	Ulti_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Ulti_Bar")));
	UltiHighlight_Image = Cast<UImage>(GetWidgetFromName(TEXT("Ulti_Highlight")));

	if (UltiHighlight_Image) {
		struct FLinearColor* color = new FLinearColor(0, 0, 0, 0);

		UltiHighlight_Image->SetColorAndOpacity(*color);
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
	float percent = _currentUlti / _MaxUlti;

	if (percent <= 0.0f) {
		percent = 0.0f;
	}
	else if (percent >= 1.0f) {
		percent = 1.0f;
		if (UltiHighlight_Image) {
			struct FLinearColor* color = new FLinearColor(1, 1, 1, 1);

			UltiHighlight_Image->SetColorAndOpacity(*color);
		}
	}

	Ulti_ProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Ulti_Bar")));
	if (Ulti_ProgressBar) {
		Ulti_ProgressBar->SetPercent(percent);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Ulti_ProgressBar not find"));
	}
}

