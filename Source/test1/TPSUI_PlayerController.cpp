// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSUI_PlayerController.h"
#include "Blueprint/UserWidget.h"

void ATPSUI_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!UIWidgetClass) return;

	UIWidgetInstance = CreateWidget<UTitle_UserWidget>(this, UIWidgetClass);
	UIWidgetInstance->AddToViewport();

	if (!UIWidgetInstance) return;

	FInputModeUIOnly Mode;	
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}
