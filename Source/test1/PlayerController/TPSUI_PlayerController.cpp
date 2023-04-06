// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSUI_PlayerController.h"
#include "Blueprint/UserWidget.h"

void ATPSUI_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!UIWidgetClass) return;

	// 타이틀UI 생성 및 띄우기
	UIWidgetInstance = CreateWidget<UTitle_UserWidget>(this, UIWidgetClass);
	UIWidgetInstance->AddToViewport();
		
	if (!UIWidgetInstance) return;

	// 입력 상태를 UIONly로 설정
	FInputModeUIOnly Mode;	
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	// 마우스 커서 보임
	bShowMouseCursor = true;
}
