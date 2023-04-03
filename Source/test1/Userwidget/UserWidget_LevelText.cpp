// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_LevelText.h"

void UUserWidget_LevelText::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Comments = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Comments")));
}

void UUserWidget_LevelText::SetComments_StartStage(int32 stage)
{
	Text_Comments = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Comments")));
	if (Text_Comments) {
		FString str = "Stage " + FString::FormatAsNumber(stage);

		Text_Comments->SetText(FText::FromString(str));
	}	
}

void UUserWidget_LevelText::SetComments_Reward()
{
	Text_Comments = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Comments")));
	if (Text_Comments) {
		FString str = "Stage Clear!! Please Select Reward";

		Text_Comments->SetText(FText::FromString(str));
	}
}

void UUserWidget_LevelText::SetComments_GameClear()
{
	Text_Comments = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Comments")));
	if (Text_Comments) {
		FString str = "   Game Clear!!   ";

		Text_Comments->SetText(FText::FromString(str));
	}
}
