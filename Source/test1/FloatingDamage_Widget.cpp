// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingDamage_Widget.h"

void UFloatingDamage_Widget::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);
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

void UFloatingDamage_Widget::SetDamage(float TakeDamege)
{
	lifeTime = 1.0f;
	damage = FText::AsNumber(TakeDamege);
	floatingDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("floating_Damage")));
	if (floatingDamage) {
		floatingDamage->SetText(damage);
	}
	
	
}

void UFloatingDamage_Widget::DeleteDamage()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("delete"));
	RemoveFromParent();	
}
