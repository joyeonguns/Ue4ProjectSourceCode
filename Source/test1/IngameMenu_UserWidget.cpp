// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameMenu_UserWidget.h"
#include <Kismet/KismetSystemLibrary.h>
#include "TPSPlayerController.h"
#include <Kismet/GameplayStatics.h>

void UIngameMenu_UserWidget::NativeConstruct()
{
	BTN_Return = Cast<UButton>(GetWidgetFromName(TEXT("Button_Cancle")));

	BTN_ToLobby = Cast<UButton>(GetWidgetFromName(TEXT("Button_ToLobby")));

	BTN_ToTitle = Cast<UButton>(GetWidgetFromName(TEXT("Button_ToTitle")));


	BTN_Return->OnClicked.AddDynamic(this, &UIngameMenu_UserWidget::OnClickedReturn);
	BTN_ToLobby->OnClicked.AddDynamic(this, &UIngameMenu_UserWidget::OnClickedToLobby);
	BTN_ToTitle->OnClicked.AddDynamic(this, &UIngameMenu_UserWidget::OnClickedToTitle);
}

void UIngameMenu_UserWidget::OnClickedReturn()
{
	auto playerController = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (playerController) {
		playerController->CloseInGameMenu();
	}
}

void UIngameMenu_UserWidget::OnClickedToLobby()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Lobby_Level"));
}

void UIngameMenu_UserWidget::OnClickedToTitle()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Title_Level"));
}
