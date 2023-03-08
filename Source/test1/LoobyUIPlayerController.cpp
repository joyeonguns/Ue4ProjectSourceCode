// Fill out your copyright notice in the Description page of Project Settings.


#include "LoobyUIPlayerController.h"

void ALoobyUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!UIWidgetClass) return;

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	UIWidgetInstance->AddToViewport();

	if (!UIWidgetInstance) return;

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Loby"));
}
