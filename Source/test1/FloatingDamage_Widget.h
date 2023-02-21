// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "FloatingDamage_Widget.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UFloatingDamage_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& Geometry, float DeltaSeconds) override;
	virtual void NativeConstruct() override;
	void SetDamage(float TakeDamege);
	void DeleteDamage();

private:

	FText damage;
	float lifeTime;

	UPROPERTY()
	class UTextBlock* floatingDamage;
};
