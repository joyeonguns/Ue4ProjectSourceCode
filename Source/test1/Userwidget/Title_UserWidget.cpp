// Fill out your copyright notice in the Description page of Project Settings.


#include "Title_UserWidget.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "TPSGameModeBase.h"
#include "TPSGameInstance.h"

void UTitle_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BTN_GameStart = Cast<UButton>(GetWidgetFromName(TEXT("Button_GameStart")));

	BTN_GameEnd = Cast<UButton>(GetWidgetFromName(TEXT("Button_GameEnd")));

	BTN_GameStart->OnClicked.AddDynamic(this, &UTitle_UserWidget::GameStartCallback);
	BTN_GameEnd->OnClicked.AddDynamic(this, &UTitle_UserWidget::GameEndCallback);

	// GameInstace의 정보 수정
	auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameinstance) {
		// statusArray 값 0으로 초기화
		gameinstance->statusArray.Init(0, 8);
		// point 초기화
		gameinstance->Point = 1000;
	}
	
}

void UTitle_UserWidget::GameStartCallback()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Game Start Button"));	
	UGameplayStatics::OpenLevel(GetWorld(), FName("Lobby_Level"));
	
}

void UTitle_UserWidget::GameEndCallback()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Game End Button"));
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
