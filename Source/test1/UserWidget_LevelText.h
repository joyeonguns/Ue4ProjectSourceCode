// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "UserWidget_LevelText.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API UUserWidget_LevelText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void SetComments_StartStage(int32 stage);
	void SetComments_Reward();


private:
	UPROPERTY()
		class UTextBlock* Text_Comments;
};
