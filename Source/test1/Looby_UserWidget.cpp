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
	BTN_GoWeapon->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_GoWeaponBTN);
	BTN_GoInGame->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_GoInGameBTN);
	BTN_GoTitle->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_GoTitleBTN);

	// CanvasPannel
	StatPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Panel_Stat")));
	WeaponPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Panel_Weapon")));
	InGamePanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Panel_InGame")));

	// StatButton
	BTN_DecStat_0 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_0")));
	BTN_AddStat_0 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_0")));
	Text_NumStat_0 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_0")));
	
	BTN_DecStat_0->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_0);
	BTN_AddStat_0->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_0);


	BTN_DecStat_1 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_1")));
	BTN_AddStat_1 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_1")));
	Text_NumStat_1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_1")));

	BTN_DecStat_1->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_1);
	BTN_AddStat_1->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_1);


	BTN_DecStat_2 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_2")));
	BTN_AddStat_2 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_2")));
	Text_NumStat_2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_2")));

	BTN_DecStat_2->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_2);
	BTN_AddStat_2->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_2);


	BTN_DecStat_3 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_3")));
	BTN_AddStat_3 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_3")));
	Text_NumStat_3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_3")));

	BTN_DecStat_3->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_3);
	BTN_AddStat_3->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_3);


	BTN_DecStat_4 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_4")));
	BTN_AddStat_4 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_4")));
	Text_NumStat_4 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_4")));

	BTN_DecStat_4->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_4);
	BTN_AddStat_4->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_4);


	BTN_DecStat_5 = Cast<UButton>(GetWidgetFromName(TEXT("Button-_Stat_5")));
	BTN_AddStat_5 = Cast<UButton>(GetWidgetFromName(TEXT("Button_+_Stat_5")));
	Text_NumStat_5 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Stat_5")));

	BTN_DecStat_5->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_DesStatBTN_5);
	BTN_AddStat_5->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_AddStatBTN_5);





	poinText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Point")));



	//// WeaponBookPage
	//Img_Weapon_0 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_0")));
	//Img_Weapon_1 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_1")));
	//Img_Weapon_2 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_2")));
	//Img_Weapon_3 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_3")));
	//Img_Weapon_4 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_4")));
	//Img_Weapon_5 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_5")));
	//Img_Weapon_6 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_6")));
	//Img_Weapon_7 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_7")));
	//Img_Weapon_8 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_8")));
	//Img_Weapon_9 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_9")));
	//Img_Weapon_10 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_10")));
	//Img_Weapon_11 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Weapon_11")));

	//WeaponBook.Add(Img_Weapon_0);
	//WeaponBook.Add(Img_Weapon_1);
	//WeaponBook.Add(Img_Weapon_2);
	//WeaponBook.Add(Img_Weapon_3);
	//WeaponBook.Add(Img_Weapon_4);
	//WeaponBook.Add(Img_Weapon_5);
	//WeaponBook.Add(Img_Weapon_6);
	//WeaponBook.Add(Img_Weapon_7);
	//WeaponBook.Add(Img_Weapon_8);
	//WeaponBook.Add(Img_Weapon_9);
	//WeaponBook.Add(Img_Weapon_10);
	//WeaponBook.Add(Img_Weapon_11);



	// InGame
	BTN_GameStart = Cast<UButton>(GetWidgetFromName(TEXT("Button_GameStart")));

	BTN_SelectWeapon_0 = Cast<UButton>(GetWidgetFromName(TEXT("Button_IngameWeapon_0")));
	BTN_SelectWeapon_1 = Cast<UButton>(GetWidgetFromName(TEXT("Button_IngameWeapon_1")));
	BTN_SelectWeapon_2 = Cast<UButton>(GetWidgetFromName(TEXT("Button_IngameWeapon_2")));


	BTN_GameStart->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_GameStart);

	BTN_SelectWeapon_0->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_SelectWeapon_0);
	BTN_SelectWeapon_1->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_SelectWeapon_1);
	BTN_SelectWeapon_2->OnClicked.AddDynamic(this, &ULooby_UserWidget::OnClicked_SelectWeapon_2);
	
	OnClicked_SelectWeapon_0();
	OnClicked_GoStatBTN();
	TakeStatusArray();

	//point = 999999;
	
	SetStatState();

	inactiveColor.R = 1.0f;
	inactiveColor.G = 1.0f;
	inactiveColor.B = 1.0f;
	inactiveColor.A = 1.0f;

	activeColor.R = 1.0f;
	activeColor.G = 1.0f;
	activeColor.B = 1.0f;
	activeColor.A = 0.5f;

	/*for (int i = 0; i < 12; i++) {
		WeaponBook[i]->SetColorAndOpacity(FLinearColor::Black);
	}
	for (int i = 0; i < UnLockArray.Num(); i++) {
		int n = UnLockArray[i];
		WeaponBook[n]->SetColorAndOpacity(FLinearColor::White);
	}*/
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

void ULooby_UserWidget::OnClicked_GoWeaponBTN()
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
	Text_NumStat_0->SetText(FText::AsNumber(statusArray[0]));
	Text_NumStat_1->SetText(FText::AsNumber(statusArray[1]));
	Text_NumStat_2->SetText(FText::AsNumber(statusArray[2]));
	Text_NumStat_3->SetText(FText::AsNumber(statusArray[3]));
	Text_NumStat_4->SetText(FText::AsNumber(statusArray[4]));
	Text_NumStat_5->SetText(FText::AsNumber(statusArray[5]));
	/*Text_NumStat_6->SetText(FText::AsNumber(statusArray[6]));
	Text_NumStat_7->SetText(FText::AsNumber(statusArray[7]));*/

	poinText->SetText(FText::AsNumber(point));
}

void ULooby_UserWidget::OnClicked_AddStatBTN_0()
{
	int32 price = pow(10, statusArray[0]);

	if (statusArray[0] < 5 && point > price) {
		point -= price;
		statusArray[0] = statusArray[0] + 1;
		SetStatState();

		BTN_DecStat_0->SetIsEnabled(true);
		if (statusArray[0] == 5) {
			BTN_AddStat_0->SetIsEnabled(false);
		}
	}	
}

void ULooby_UserWidget::OnClicked_DesStatBTN_0()
{
	int32 price = pow(10, statusArray[0] - 1);

	if (statusArray[0] > 0) {
		statusArray[0] = statusArray[0] - 1;
		point += price;
		SetStatState();

		BTN_AddStat_0->SetIsEnabled(true);
		if (statusArray[0] == 0) {
			BTN_DecStat_0->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_AddStatBTN_1()
{
	int32 price = pow(10, statusArray[1]);

	if (statusArray[1] < 5 && point > price) {
		point -= price;
		statusArray[1] = statusArray[1] + 1;
		SetStatState();

		BTN_DecStat_1->SetIsEnabled(true);
		if (statusArray[1] == 5) {
			BTN_AddStat_1->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_DesStatBTN_1()
{
	int32 price = pow(10, statusArray[1] - 1);

	if (statusArray[1] > 0) {
		statusArray[1] = statusArray[1] - 1;
		point += price;
		SetStatState();

		BTN_AddStat_1->SetIsEnabled(true);
		if (statusArray[1] == 0) {
			BTN_DecStat_1->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_AddStatBTN_2()
{
	int32 price = pow(10, statusArray[2]);

	if (statusArray[2] < 5 && point > price) {
		point -= price;
		statusArray[2] = statusArray[2] + 1;
		SetStatState();

		BTN_DecStat_2->SetIsEnabled(true);
		if (statusArray[2] == 5) {
			BTN_AddStat_2->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_DesStatBTN_2()
{
	int32 price = pow(10, statusArray[2] - 1);

	if (statusArray[2] > 0) {
		statusArray[2] = statusArray[2] - 1;
		point += price;
		SetStatState();

		BTN_AddStat_2->SetIsEnabled(true);
		if (statusArray[2] == 0) {
			BTN_DecStat_2->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_AddStatBTN_3()
{
	int32 price = pow(10, statusArray[3]);

	if (statusArray[3] < 5 && point > price) {
		point -= price;
		statusArray[3] = statusArray[3] + 1;
		SetStatState();

		BTN_DecStat_3->SetIsEnabled(true);
		if (statusArray[3] == 5) {
			BTN_AddStat_3->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_DesStatBTN_3()
{
	int32 price = pow(10, statusArray[3] - 1);
	
	if (statusArray[3] > 0) {
		statusArray[3] = statusArray[3] - 1;
		point += price;
		SetStatState();

		BTN_AddStat_3->SetIsEnabled(true);
		if (statusArray[3] == 0) {
			BTN_DecStat_3->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_AddStatBTN_4()
{
	int32 price = pow(10, statusArray[4]);

	if (statusArray[4] < 5 && point > price) {
		point -= price;
		statusArray[4] = statusArray[4] + 1;
		SetStatState();

		BTN_DecStat_4->SetIsEnabled(true);
		if (statusArray[4] == 5) {
			BTN_AddStat_4->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_DesStatBTN_4()
{
	int32 price = pow(10, statusArray[4] - 1);

	if (statusArray[4] > 0) {
		statusArray[4] = statusArray[4] - 1;
		point += price;
		SetStatState();

		BTN_AddStat_4->SetIsEnabled(true);
		if (statusArray[4] == 0) {
			BTN_DecStat_4->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_AddStatBTN_5()
{
	int32 price = pow(10, statusArray[5]);

	if (statusArray[5] < 5 && point > price) {
		point -= price;
		statusArray[5] = statusArray[5] + 1;
		SetStatState();

		BTN_DecStat_5->SetIsEnabled(true);
		if (statusArray[5] == 5) {
			BTN_AddStat_5->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_DesStatBTN_5()
{
	int32 price = pow(10, statusArray[5] - 1);

	if (statusArray[5] > 0) {
		statusArray[5] = statusArray[5] - 1;
		point += price;
		SetStatState();

		BTN_AddStat_5->SetIsEnabled(true);
		if (statusArray[5] == 0) {
			BTN_DecStat_5->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_AddStatBTN_6()
{
	int32 price = pow(10, statusArray[6]);

	if (statusArray[6] < 5 && point > price) {
		point -= price;
		statusArray[6] = statusArray[6] + 1;
		SetStatState();

		BTN_DecStat_6->SetIsEnabled(true);
		if (statusArray[6] == 5) {
			BTN_AddStat_6->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_DesStatBTN_6()
{
	int32 price = pow(10, statusArray[6] - 1);


	if (statusArray[6] > 0) {
		statusArray[6] = statusArray[6] - 1;
		point += price;
		SetStatState();

		BTN_AddStat_6->SetIsEnabled(true);
		if (statusArray[6] == 0) {
			BTN_DecStat_6->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_AddStatBTN_7()
{
	int32 price = pow(10, statusArray[7]);


	if (statusArray[7] < 5 && point > price) {
		point -= price;
		statusArray[7] = statusArray[7] + 1;
		SetStatState();

		BTN_DecStat_7->SetIsEnabled(true);
		if (statusArray[7] == 5) {
			BTN_AddStat_7->SetIsEnabled(false);
		}
	}
}

void ULooby_UserWidget::OnClicked_DesStatBTN_7()
{
	int32 price = pow(10, statusArray[7]-1);

	if (statusArray[7] > 0) {
		statusArray[7] = statusArray[7] - 1;
		point += price;
		SetStatState();

		BTN_AddStat_7->SetIsEnabled(true);
		if (statusArray[7] == 0) {
			BTN_DecStat_7->SetIsEnabled(false);
		}
	}
}


void ULooby_UserWidget::TakeStatusArray()
{
	auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameinstance) {
		statusArray.Init(1, 8);
		statusArray = gameinstance->statusArray;
		UnLockArray = gameinstance->UnLockItemList;

		point = gameinstance->Point;
	}
	
}





//****** Ingame *****
void ULooby_UserWidget::OnClicked_GameStart()
{
	auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameinstance) {
		gameinstance->statusArray = statusArray;
		gameinstance->SelectedWeaponCode = SelectWeaponCode;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("TPS_InGame"));
}

void ULooby_UserWidget::OnClicked_SelectWeapon_0()
{	
	SelectWeaponCode = 1;
	BTN_SelectWeapon_0->SetRenderOpacity(1.0f);
	BTN_SelectWeapon_1->SetRenderOpacity(0.4f);
	BTN_SelectWeapon_2->SetRenderOpacity(0.4f);
}

void ULooby_UserWidget::OnClicked_SelectWeapon_1()
{
	SelectWeaponCode = 2;
	BTN_SelectWeapon_0->SetRenderOpacity(0.4f);
	BTN_SelectWeapon_1->SetRenderOpacity(1.0f); 
	BTN_SelectWeapon_2->SetRenderOpacity(0.4f);
}

void ULooby_UserWidget::OnClicked_SelectWeapon_2()
{
	SelectWeaponCode = 3;
	BTN_SelectWeapon_0->SetRenderOpacity(0.4f);
	BTN_SelectWeapon_1->SetRenderOpacity(0.4f);
	BTN_SelectWeapon_2->SetRenderOpacity(1.0f);
}

