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
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("stat_0 lvl : ")) + FString::FromInt(lvl));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("SelectWeapon : ")) + FString::FromInt(gameinstance->SelectedWeaponCode));

		auto player = Cast<ATPS_Character>(this->GetPawn());
		if (player) {
			//int32 itemcode = gameinstance->SelectedWeaponCode;
			player->SpawnDefaultInventory(0);
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

void ATPSPlayerController::InputKeyESC()
{
	OpenInGameMenu();

	//if (bOpenInGameMenu) {
	//	bOpenInGameMenu = false;
	//	CloseInGameMenu();
	//}
	//else {
	//	bOpenInGameMenu = true;
	//	OpenInGameMenu();
	//}	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("InputKeyESC ")));

}

void ATPSPlayerController::OpenInGameMenu()
{
	if (!InGameMenu_Instance) {
		InGameMenu_Instance = CreateWidget<UIngameMenu_UserWidget>(this, InGameMenu_Class);
	}


	if (InGameMenu_Instance) {
		InGameMenu_Instance->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		FInputModeGameAndUI Mode;
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
		InGameMenu_Instance->RemoveFromViewport();

		FInputModeGameOnly Mode;
		SetInputMode(Mode);
		bShowMouseCursor = false;
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

void ATPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("ESC"), IE_Pressed, this, &ATPSPlayerController::InputKeyESC);
	InputComponent->BindAction(TEXT("TAP"), IE_Pressed, this, &ATPSPlayerController::InputKeyTap);

}

void ATPSPlayerController::HUDCoolDownUpdate(float Def_CoolTime_Q, float currentCoolTime_Q,
	float Def_CoolTime_E, float currentCoolTime_E,
	float Def_CoolTime_1, float currentCoolTime_1,
	float Def_CoolTime_2, float currentCoolTime_2)
{
	if (Hud) {
		Hud->SetProgressBar_Skill_Q(currentCoolTime_Q / Def_CoolTime_Q, Def_CoolTime_Q - currentCoolTime_Q);
		Hud->SetProgressBar_Skill_E(currentCoolTime_E / Def_CoolTime_E, Def_CoolTime_E - currentCoolTime_E);
		Hud->SetProgressBar_Item_1(currentCoolTime_1 / Def_CoolTime_1, Def_CoolTime_1 - currentCoolTime_1);
		Hud->SetProgressBar_Item_2(currentCoolTime_2 / Def_CoolTime_2, Def_CoolTime_2 - currentCoolTime_2);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Hud not find"));
	}
}

void ATPSPlayerController::OpenInteractionUI()
{
	InteractionUI_Instance = CreateWidget<UUserWidget>(this, InteractionUI_Class);

	if (InteractionUI_Instance) {
		InteractionUI_Instance->AddToViewport();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Menu not find"));
	}
}

void ATPSPlayerController::CloseInteractionUI()
{
	auto player = Cast<ATPS_Character>(this->GetPawn());
	if (InteractionUI_Instance && !player->GetbDead()) {
		InteractionUI_Instance->RemoveFromViewport();
	}
}

void ATPSPlayerController::InputKeyTap()
{
	OpenInGameData();
}

void ATPSPlayerController::OpenInGameData()
{
	if (!StageDatawidget_Instance) {
		StageDatawidget_Instance = CreateWidget<UUserWidget_InGameData>(this, StageDatawidget_Class);
		if (StageDatawidget_Instance) {
			StageDatawidget_Instance->DefaultUISetting();
			StageDatawidget_Instance->OnExitInGameDataWidget.Clear();
			StageDatawidget_Instance->OnExitInGameDataWidget.AddUObject(this, &ATPSPlayerController::CloseInGameData);

			StageDatawidget_Instance->AddToViewport();

			CloseInGameData();
		}
	}


	if (StageDatawidget_Instance) {
		StageDatawidget_Instance->DefaultUISetting();
		StageDatawidget_Instance->OnExitInGameDataWidget.Clear();
		StageDatawidget_Instance->OnExitInGameDataWidget.AddUObject(this, &ATPSPlayerController::CloseInGameData);

		StageDatawidget_Instance->AddToViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), true);

		FInputModeGameAndUI Mode;
		SetInputMode(Mode);
		bShowMouseCursor = true;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Menu not find"));
	}
}

void ATPSPlayerController::CloseInGameData()
{
	if (StageDatawidget_Instance) {
		StageDatawidget_Instance->RemoveFromViewport();

		FInputModeGameOnly Mode;
		SetInputMode(Mode);
		bShowMouseCursor = false;
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

