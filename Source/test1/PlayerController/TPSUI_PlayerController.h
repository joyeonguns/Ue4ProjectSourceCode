// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Title_UserWidget.h"
#include "TPSUI_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ATPSUI_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = UI)
		TSubclassOf<class UTitle_UserWidget> UIWidgetClass;

	UPROPERTY()
		class UTitle_UserWidget* UIWidgetInstance;

};
