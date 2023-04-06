// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingDamage_Widget.h"
#include "Styling/SlateTypes.h"

void UFloatingDamage_Widget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

	// 지속시간이 0이되면 UI 제거
	lifeTime -= DeltaSeconds;
	if (lifeTime <= 0.0f) {
		DeleteDamage();
	}
}

void UFloatingDamage_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	lifeTime = 1.0f;

	floatingDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("floating_Damage")));
}

void UFloatingDamage_Widget::SetDamage(float TakeDamege, bool cri)
{
	lifeTime = 1.0f;

	// damage 및 floatingDamage  할당
	damage = FText::AsNumber(TakeDamege);
	floatingDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("floating_Damage")));

	Image_Cri = Cast<UImage>(GetWidgetFromName(TEXT("Image_Critical")));

	if (floatingDamage && Image_Cri) {
		floatingDamage->SetText(damage);

		// 크리티컬 O -> 이미지 Visible
		if (cri) {
			Image_Cri->SetVisibility(ESlateVisibility::Visible);
		}
		// 크리티컬 X -> 이미지 Hidden
		else {
			Image_Cri->SetVisibility(ESlateVisibility::Hidden);
		}
	}	
}

void UFloatingDamage_Widget::DeleteDamage()
{
	// UI 제거
	RemoveFromViewport();	
}


