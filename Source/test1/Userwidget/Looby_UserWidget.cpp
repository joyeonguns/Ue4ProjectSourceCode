// Fill out your copyright notice in the Description page of Project Settings.


#include "Looby_UserWidget.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "TPSGameInstance.h"

void ULooby_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 상단 버튼
	BTN_GoStat = Cast<UButton>(GetWidgetFromName(TEXT("Button_StatPage_0")));
	BTN_GoWeapon = Cast<UButton>(GetWidgetFromName(TEXT("Button_WeaponPage")));
	BTN_GoInGame = Cast<UButton>(GetWidgetFromName(TEXT("Button_InGamePage")));
	BTN_GoTitle = Cast<UButton>(GetWidgetFromName(TEXT("Button_Title")));

	BTN_GoStat->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_GoStatBTN);
	BTN_GoWeapon->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_GoDataBTN);
	BTN_GoInGame->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_GoInGameBTN);
	BTN_GoTitle->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_GoTitleBTN);

	// CanvasPannel
	StatPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Panel_Stat")));
	WeaponPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Panel_Weapon")));
	InGamePanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Panel_InGame")));

	// StatButton
	// 버튼 연결 및 배열에 추가
	BTN_DesStat_0 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_0")));
	BTN_AddStat_0 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_0")));
	Text_NumStat_0 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_0")));
	Text_StatComent_0 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StatComent_0")));
	
	BTN_DesStat_0->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_0);
	BTN_AddStat_0->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_0);

	AddButtonArray.Add(BTN_AddStat_0);
	DesButtonArray.Add(BTN_DesStat_0);
	StatNumArray.Add(Text_NumStat_0);
	StatCommentArray.Add(Text_StatComent_0);


	BTN_DesStat_1 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_1")));
	BTN_AddStat_1 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_1")));
	Text_NumStat_1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_1")));
	Text_StatComent_1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StatComent_1")));

	BTN_DesStat_1->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_1);
	BTN_AddStat_1->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_1);

	AddButtonArray.Add(BTN_AddStat_1);
	DesButtonArray.Add(BTN_DesStat_1);
	StatNumArray.Add(Text_NumStat_1);
	StatCommentArray.Add(Text_StatComent_1);


	BTN_DesStat_2 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_2")));
	BTN_AddStat_2 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_2")));
	Text_NumStat_2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_2")));
	Text_StatComent_2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StatComent_2")));

	BTN_DesStat_2->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_2);
	BTN_AddStat_2->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_2);

	AddButtonArray.Add(BTN_AddStat_2);
	DesButtonArray.Add(BTN_DesStat_2);
	StatNumArray.Add(Text_NumStat_2);
	StatCommentArray.Add(Text_StatComent_2);


	BTN_DesStat_3 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_3")));
	BTN_AddStat_3 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_3")));
	Text_NumStat_3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_3")));
	Text_StatComent_3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StatComent_3")));

	BTN_DesStat_3->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_3);
	BTN_AddStat_3->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_3);

	AddButtonArray.Add(BTN_AddStat_3);
	DesButtonArray.Add(BTN_DesStat_3);
	StatNumArray.Add(Text_NumStat_3);
	StatCommentArray.Add(Text_StatComent_3);


	BTN_DesStat_4 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_4")));
	BTN_AddStat_4 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_4")));
	Text_NumStat_4 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_4")));
	Text_StatComent_4 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StatComent_4")));

	BTN_DesStat_4->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_4);
	BTN_AddStat_4->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_4);

	AddButtonArray.Add(BTN_AddStat_4);
	DesButtonArray.Add(BTN_DesStat_4);
	StatNumArray.Add(Text_NumStat_4);
	StatCommentArray.Add(Text_StatComent_4);


	BTN_DesStat_5 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_5")));
	BTN_AddStat_5 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_5")));
	Text_NumStat_5 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_5")));
	Text_StatComent_5 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StatComent_5")));

	BTN_DesStat_5->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_5);
	BTN_AddStat_5->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_5);

	AddButtonArray.Add(BTN_AddStat_5);
	DesButtonArray.Add(BTN_DesStat_5);
	StatNumArray.Add(Text_NumStat_5);
	StatCommentArray.Add(Text_StatComent_5);



	// 포인트 연결
	poinText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Point")));


	// InGame
	BTN_GameStart = Cast<UButton>(GetWidgetFromName(TEXT("Button_GameStart")));

	BTN_SelectWeapon_0 = Cast<UButton>(GetWidgetFromName(TEXT("Button_IngameWeapon_0")));
	BTN_SelectWeapon_1 = Cast<UButton>(GetWidgetFromName(TEXT("Button_IngameWeapon_1")));
	BTN_SelectWeapon_2 = Cast<UButton>(GetWidgetFromName(TEXT("Button_IngameWeapon_2")));


	BTN_GameStart->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_GameStart);

	BTN_SelectWeapon_0->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_SelectSchool_1);
	BTN_SelectWeapon_1->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_SelectSchool_2);
	BTN_SelectWeapon_2->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_SelectSchool_3);
	

	// 기본 세팅 StatPage, 특성1 Fire 선택
	OnClicked_SelectSchool_1();
	OnClicked_GoStatBTN();

	// 게임인스턴스에서 능력치 업그레이드 배열 가져옴 
	TakeStatusArray();

	// 능력치 업그레이드 텍스트 세팅
	SetStatState();
}

//***** Top Button *******
void ULooby_UserWidget::OnClicked_GoStatBTN()
{
	StatPanel->SetVisibility(ESlateVisibility::Visible);
	WeaponPanel->SetVisibility(ESlateVisibility::Hidden);
	InGamePanel->SetVisibility(ESlateVisibility::Hidden);


	BTN_GoStat->SetRenderOpacity(1.0f);
	BTN_GoWeapon->SetRenderOpacity(0.7f);
	BTN_GoInGame->SetRenderOpacity(0.7f);
	BTN_GoTitle->SetRenderOpacity(0.7f);
}

void ULooby_UserWidget::OnClicked_GoDataBTN()
{
	StatPanel->SetVisibility(ESlateVisibility::Hidden);
	WeaponPanel->SetVisibility(ESlateVisibility::Visible);
	InGamePanel->SetVisibility(ESlateVisibility::Hidden);

	BTN_GoStat->SetRenderOpacity(0.7f);
	BTN_GoWeapon->SetRenderOpacity(1.0f);
	BTN_GoInGame->SetRenderOpacity(0.7f);
	BTN_GoTitle->SetRenderOpacity(0.7f);
}

void ULooby_UserWidget::OnClicked_GoInGameBTN()
{
	StatPanel->SetVisibility(ESlateVisibility::Hidden);
	WeaponPanel->SetVisibility(ESlateVisibility::Hidden);
	InGamePanel->SetVisibility(ESlateVisibility::Visible);

	BTN_GoStat->SetRenderOpacity(0.7f);
	BTN_GoWeapon->SetRenderOpacity(0.7f);
	BTN_GoInGame->SetRenderOpacity(1.0f);
	BTN_GoTitle->SetRenderOpacity(0.7f);
}

void ULooby_UserWidget::OnClicked_GoTitleBTN()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Title_Level"));
}
//***** Top Button *******




//***** Stat Button *******
void ULooby_UserWidget::SetStatState()
{	
	// 능력치 텍스트 값 저장
	for (int i = 0; i < 6; i++) {
		StatNumArray[i]->SetText(FText::AsNumber(statusArray[i]));


		auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (gameinstance) {

			// 능력치 코멘트 설정
			FString str = "";
			switch (i)
			{
			case 0:
				str = "+ " + FString::FormatAsNumber(gameinstance->Get_FStatusLevel(statusArray[i])->Hp);
				break;
			case 1:
				str = "+ " + FString::FormatAsNumber(gameinstance->Get_FStatusLevel(statusArray[i])->Damage);
				break;
			case 2:
				str = "+ " + FString::FormatAsNumber(gameinstance->Get_FStatusLevel(statusArray[i])->Critical) + "%";
				break;
			case 3:
				str = "+ " + FString::FormatAsNumber(gameinstance->Get_FStatusLevel(statusArray[i])->CoolTime);
				break;
			case 4:
				str = "+ " + FString::FormatAsNumber(statusArray[i]);
				break;
			case 5:
				str = "+ " + FString::FormatAsNumber(statusArray[i] * 10) + "%";
				break;
			default:
				break;
			}

			// 능력치 코멘트 저장
			StatCommentArray[i]->SetText(FText::FromString(str));
		}		
	}

	

	// 포인트 값 저장
	poinText->SetText(FText::AsNumber(point));
}

void ULooby_UserWidget::AddStatus(int32 num)
{
	// 포인트 코스트
	int32 price = pow(10, statusArray[num]);

	// 능력치 + 조건
	if (statusArray[num] < 5 && point > price) {
		point -= price;
		statusArray[num] = statusArray[num] + 1;
		// 능력치 업그레이트 텍스트 수정
		SetStatState();

		// 업그레이드 감소버튼 활성화
		DesButtonArray[num]->SetIsEnabled(true);

		// 업그레이드가 5단계가 될경우 증가버튼 비활성화 
		if (statusArray[num] == 5) {
			AddButtonArray[num]->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::DesStatus(int32 num)
{
	// 포인트 코스트
	int32 price = pow(10, statusArray[num] - 1);

	// 능력치 - 조건
	if (statusArray[num] > 0) {
		statusArray[num] = statusArray[num] - 1;
		point += price;
		// 능력치 텍스트 설정
		SetStatState();

		// 업그레이드 증가 버튼 활성화
		AddButtonArray[num]->SetIsEnabled(true);
		// 업그레이드 0일 경우 감소 버튼 활성화
		if (statusArray[num] == 0) {
			DesButtonArray[num]->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_AddStatBTN_0()
{
	AddStatus(0);
}

void ULooby_UserWidget::OnClicked_DesStatBTN_0()
{
	DesStatus(0);
}

void ULooby_UserWidget::OnClicked_AddStatBTN_1()
{
	AddStatus(1);
}

void ULooby_UserWidget::OnClicked_DesStatBTN_1()
{
	DesStatus(1);
}

void ULooby_UserWidget::OnClicked_AddStatBTN_2()
{
	AddStatus(2);
}

void ULooby_UserWidget::OnClicked_DesStatBTN_2()
{
	DesStatus(2);
}

void ULooby_UserWidget::OnClicked_AddStatBTN_3()
{
	AddStatus(3);
}

void ULooby_UserWidget::OnClicked_DesStatBTN_3()
{
	DesStatus(3);
}

void ULooby_UserWidget::OnClicked_AddStatBTN_4()
{
	AddStatus(4);
}

void ULooby_UserWidget::OnClicked_DesStatBTN_4()
{
	DesStatus(4);
}

void ULooby_UserWidget::OnClicked_AddStatBTN_5()
{
	AddStatus(5);
}

void ULooby_UserWidget::OnClicked_DesStatBTN_5()
{
	DesStatus(5);	
}



void ULooby_UserWidget::TakeStatusArray()
{
	auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameinstance) {
		//능력치 업그레이드 배열 정보 저장
		statusArray.Init(1, 8);
		statusArray = gameinstance->statusArray;

		// 포인트 저장
		point = gameinstance->Point;
	}
	
}





//****** Ingame *****
void ULooby_UserWidget::OnClicked_GameStart()
{
	// 로비에서 설정한 정보를 Gameinstance에 저장
	auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameinstance) {
		gameinstance->statusArray = statusArray;
		gameinstance->SelectedSchoolCode = SelectSchool;
		gameinstance->Point = point;
	}

	// 전투 월드레벨로 이동
	UGameplayStatics::OpenLevel(GetWorld(), FName("GreenwoodVillage_demoMap"));	
}

void ULooby_UserWidget::OnClicked_SelectSchool_1()
{	
	// 특성1 Fire 선택
	SelectSchool = 1;
	BTN_SelectWeapon_0->SetRenderOpacity(1.0f);
	BTN_SelectWeapon_1->SetRenderOpacity(0.4f);
	BTN_SelectWeapon_2->SetRenderOpacity(0.4f);
}

void ULooby_UserWidget::OnClicked_SelectSchool_2()
{
	// 특성2 Volt 선택
	SelectSchool = 2;
	BTN_SelectWeapon_0->SetRenderOpacity(0.4f);
	BTN_SelectWeapon_1->SetRenderOpacity(1.0f); 
	BTN_SelectWeapon_2->SetRenderOpacity(0.4f);
}

void ULooby_UserWidget::OnClicked_SelectSchool_3()
{
	// 특성3 Aqua 선택
	SelectSchool = 3;
	BTN_SelectWeapon_0->SetRenderOpacity(0.4f);
	BTN_SelectWeapon_1->SetRenderOpacity(0.4f);
	BTN_SelectWeapon_2->SetRenderOpacity(1.0f);
}

