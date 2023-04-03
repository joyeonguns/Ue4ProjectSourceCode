// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "IngameMenu_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UIngameMenu_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;


	UFUNCTION()
		void OnClickedReturn();

	UFUNCTION()
		void OnClickedToLobby();
	
	UFUNCTION()
		void OnClickedToTitle();

private:

	UPROPERTY()
		class UButton* BTN_Return;

	UPROPERTY()
		class UButton* BTN_ToLobby;

	UPROPERTY()
		class UButton* BTN_ToTitle;
};
