// Fill out your copyright notice in the Description page of Project Settings.


#include "LoobyUIPlayerController.h"

void ALoobyUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!UIWidgetClass) return;

	// 로비UI 생성 및 띄우기
	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	if (UIWidgetInstance) {
		UIWidgetInstance->AddToViewport();
	}

	if (!UIWidgetInstance) return;

	// 입력 상태를 UIONly로 설정
	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);

	// 마우스 커서 보임
	bShowMouseCursor = true;
}
