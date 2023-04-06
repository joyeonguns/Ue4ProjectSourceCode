// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "Title_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UTitle_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void GameStartCallback();

	UFUNCTION()
		void GameEndCallback();

private:	
	UPROPERTY()
		class UButton* BTN_GameStart;

	UPROPERTY()
		class UButton* BTN_GameEnd;
};
