// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_InGameData.h"
#include "TPSGameInstance.h"
#include <Kismet/GameplayStatics.h>

void UUserWidget_InGameData::NativeConstruct()
{
	Super::NativeConstruct();

	//¹öÆ°
	Btn_Exit = Cast<UButton>(GetWidgetFromName(TEXT("Button_Exit")));
	Btn_NextPage = Cast<UButton>(GetWidgetFromName(TEXT("Button_after_Page")));
	Btn_PrePage = Cast<UButton>(GetWidgetFromName(TEXT("Button_befor_Page")));

	// Text
	Text_StageNumber = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stage")));
	Text_EnenyData = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_EnemyData")));
	Text_PlayerData = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_CharacterData")));

	// Canvas
	Page_1 = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("page1")));
	Page_2 = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("page2")));

	Pages.Add(Page_1);
	Pages.Add(Page_2);

	if (Btn_Exit) {
		Btn_Exit->OnClicked.Clear();
		Btn_Exit->OnClicked.AddDynamic(this, &UUserWidget_InGameData::OnClickExitBTN);
	}
	if (Btn_NextPage) {
		Btn_NextPage->OnClicked.Clear();
		Btn_NextPage->OnClicked.AddDynamic(this, &UUserWidget_InGameData::OnClickNextPage);
	}
	if (Btn_PrePage) {
		Btn_PrePage->OnClicked.Clear();
		Btn_PrePage->OnClicked.AddDynamic(this, &UUserWidget_InGameData::OnClickNextPage);
	}

	//DefaultUISetting();

	CurrentPage = 1;
}

void UUserWidget_InGameData::DefaultUISetting()
{
	Page_1 = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("page1")));
	Page_2 = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("page2")));

	Page_1->SetVisibility(ESlateVisibility::Visible);
	Page_2->SetVisibility(ESlateVisibility::Hidden);

	Set_PlayerData();
	Set_EnemyData();
	Set_StageNumber();
}

void UUserWidget_InGameData::OnClickExitBTN()
{
	OnExitInGameDataWidget.Broadcast();
}

void UUserWidget_InGameData::OnClickNextPage()
{
	Page_1 = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("page1")));
	Page_2 = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("page2")));

	// È¦
	if ((CurrentPage % 2) == 0) {
		CurrentPage++;
		Page_1->SetVisibility(ESlateVisibility::Visible);
		Page_2->SetVisibility(ESlateVisibility::Hidden);
	}
	// Â¦
	else {
		CurrentPage++;
		Page_1->SetVisibility(ESlateVisibility::Hidden);
		Page_2->SetVisibility(ESlateVisibility::Visible);	
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT(" openpage : %d"), CurrentPage));

}

void UUserWidget_InGameData::Set_StageNumber()
{
	auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!gameinstance) return;
	int32 _number = gameinstance->Get_BattleData_Enemy()->Stage;

	FString str = "STAGE " + FString::FormatAsNumber(_number);

	if(Text_StageNumber)
		Text_StageNumber->SetText(FText::FromString(str));
}

void UUserWidget_InGameData::Set_EnemyData()
{
	auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!gameinstance) return;

	int32 _level = gameinstance->Get_BattleData_Enemy()->Level;
	int32 _Elite = gameinstance->Get_BattleData_Enemy()->Elite;
	int32 _RangeCount = gameinstance->Get_BattleData_Enemy()->Range;
	int32 _MeleeCount = gameinstance->Get_BattleData_Enemy()->Melee;
	int32 _BossCount = gameinstance->Get_BattleData_Enemy()->Boss;

	FString str = FString::FormatAsNumber(_level) + "\n \n"
		+ FString::FormatAsNumber(_Elite) + "\n \n"
		+ FString::FormatAsNumber(_RangeCount) + "\n \n"
		+ FString::FormatAsNumber(_MeleeCount) + "\n \n"
		+ FString::FormatAsNumber(_BossCount) + "\n \n";

	if (Text_EnenyData)
		Text_EnenyData->SetText(FText::FromString(str));
}

void UUserWidget_InGameData::Set_PlayerData()
{
	auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!gameinstance) return;

	int32 _Hp = gameinstance->Get_BattleData_Player()->Hp;
	int32 _Damage = gameinstance->Get_BattleData_Player()->Damage;
	int32 _Critical = gameinstance->Get_BattleData_Player()->Critical;
	int32 _Speed = gameinstance->Get_BattleData_Player()->Speed;
	int32 _Accel_CoolTime = gameinstance->Get_BattleData_Player()->Accel_CoolTime;
	int32 _RedCool = (float)(1 - 100 / (float)(100 + _Accel_CoolTime)) * 100;
	int32 _SchoolPercent = gameinstance->Get_BattleData_Player()->School_Percent;

	FString str = FString::FormatAsNumber(_Hp) + "\n \n"
		+ FString::FormatAsNumber(_Damage) + "\n \n"
		+ FString::FormatAsNumber(_Critical) + "%" + "\n \n"
		+ FString::FormatAsNumber(_Speed) + "\n \n"
		+ FString::FormatAsNumber(_Accel_CoolTime) + " (" + FString::FormatAsNumber(_RedCool) + "%) \n \n"
		+ FString::FormatAsNumber(_SchoolPercent) + "%" + "\n \n";

	if (Text_PlayerData)
		Text_PlayerData->SetText(FText::FromString(str));
}

