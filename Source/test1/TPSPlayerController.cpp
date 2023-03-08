// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"
#include "HUD_UserWidget.h"
#include "TPS_Character.h"
#include "Character_Stat_Component.h"
#include "TPSGameInstance.h"
#include <Kismet/GameplayStatics.h>

ATPSPlayerController::ATPSPlayerController()
{
}

void ATPSPlayerController::BeginPlay()
{
	OpenHUD();

	auto gameinstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameinstance) {
		int32 lvl = gameinstance->statusArray[0];
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("stat_0 lvl : ")) + FString::FromInt(lvl));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("SelectWeapon : ")) + FString::FromInt(gameinstance->SelectedWeaponCode));

		auto player = Cast<ATPS_Character>(this->GetPawn());
		if (player) {
			int32 itemcode = gameinstance->SelectedWeaponCode;
			player->SpawnDefaultInventory(itemcode);
		}
	}

	FInputModeGameOnly Mode;
	SetInputMode(Mode);
	bShowMouseCursor = false;

	

	
}

UHUD_UserWidget* ATPSPlayerController::GetHUD()
{
	return Hud;
}

void ATPSPlayerController::OpenHUD()
{
	Hud = CreateWidget<UHUD_UserWidget>(this, Hud_widgetClass);
	if (Hud) {
		Hud->SetEnemyCount(2, 2);
		Hud->SetHP(80.0f, 80.0f);
		Hud->SetUlti(60.0f, 100.0f);
		Hud->AddToViewport();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Hud not find"));
	}
}

void ATPSPlayerController::OpenInGameMenu()
{
	InGameMenu_Instance = CreateWidget<UIngameMenu_UserWidget>(this, InGameMenu_Class);
	if (InGameMenu_Instance) {
		InGameMenu_Instance->AddToViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), true);
		FInputModeUIOnly Mode;
		SetInputMode(Mode);
		bShowMouseCursor = true;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Menu not find"));
	}
}

void ATPSPlayerController::CloseInGameMenu()
{
	if (InGameMenu_Instance) {
		InGameMenu_Instance->RemoveFromParent();

		FInputModeGameOnly Mode;
		SetInputMode(Mode);
		bShowMouseCursor = false;
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

void ATPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("ESC"), IE_Pressed, this, &ATPSPlayerController::OpenInGameMenu);

}
