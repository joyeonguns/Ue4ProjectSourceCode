// Fill out your copyright notice in the Description page of Project Settings.


#include "HP_UserWidget.h"

void UHP_UserWidget::BindCharacterStat(UCharacter_Stat_Component* NewCharacterStat)
{
	if (NewCharacterStat) {
		// CurrentCharStat 연결
		CurrentCharStat = NewCharacterStat;
		// CurrentCharStat의 OnHpApply 델리케이트에 UpdateUI 연결
		NewCharacterStat->OnHpApply.AddUObject(this, &UHP_UserWidget::UpdateUI);
	}
}

UProgressBar* UHP_UserWidget::GetHpBar()
{
	return HpProgressBar;
}

void UHP_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName("HP_Bar"));
	if (HpProgressBar) {
		UpdateUI();
	}
}

void UHP_UserWidget::UpdateUI()
{
	// HPBar 적용
	if (CurrentCharStat.IsValid()) {
		if (HpProgressBar) {
			HpProgressBar->SetPercent(CurrentCharStat->GetHpRatio());
		}
	}
}
