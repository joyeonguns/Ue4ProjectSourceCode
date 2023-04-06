// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include <Components/Image.h>
#include "FloatingDamage_Widget.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UFloatingDamage_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Tick 함수
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;
	virtual void NativeConstruct() override;
	
	// 데미지 Text 적용
	void SetDamage(float TakeDamege, bool cri);
	// UI 제거
	void DeleteDamage();

private:

	// 출력할 데미지
	FText damage;
	// UI 지속시간
	float lifeTime;

	UPROPERTY()
	class UTextBlock* floatingDamage;

	// 크리티컬시 적용
	UPROPERTY()
		class UImage* Image_Cri;
};
