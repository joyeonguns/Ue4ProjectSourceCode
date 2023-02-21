// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character_Stat_Component.h"
#include "Components/ProgressBar.h"
#include "HP_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UHP_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class UCharacter_Stat_Component* NewCharacterStat);
	UProgressBar* GetHpBar();

protected:
	virtual void NativeConstruct() override;
	void UpdateUI();

private:
	TWeakObjectPtr<class UCharacter_Stat_Component> CurrentCharStat;
	UPROPERTY()
		class UProgressBar* HpProgressBar;

};
