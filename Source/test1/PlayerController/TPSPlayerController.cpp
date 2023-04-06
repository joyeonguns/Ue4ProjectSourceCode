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
	// HUD 띄우기
	OpenHUD();

	// 플레이어 무기 장착
	auto player = Cast<ATPS_Character>(this->GetPawn());
	if (player) {
		player->SpawnDefaultInventory(0);
	}

	// Input모드 GameOnly
	FInputModeGameOnly Mode;
	SetInputMode(Mode);
	// 마우스 커서 삭제
	bShowMouseCursor = false;
}


UHUD_UserWidget* ATPSPlayerController::GetHUD()
{
	return Hud;
}

void ATPSPlayerController::OpenHUD()
{
	// HUD UI 생성 및 띄우기
	Hud = CreateWidget<UHUD_UserWidget>(this, Hud_widgetClass);
	if (Hud) {
		Hud->SetHP(100, 100);
		Hud->AddToViewport();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Hud not find"));
	}
}

void ATPSPlayerController::InputKeyESC()
{
	OpenInGameMenu();
}

void ATPSPlayerController::OpenInGameMenu()
{
	// InGameMenu_Instance가 nullptr 인 경우 생성
	if (InGameMenu_Instance == nullptr) {
		InGameMenu_Instance = CreateWidget<UIngameMenu_UserWidget>(this, InGameMenu_Class);
	}

	// InGameMenu_Instance가 할당된 경우 띄우기
	if (InGameMenu_Instance) {
		InGameMenu_Instance->AddToViewport();

		// 게임을 일시정지
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// InputMode 및 마우스 커서 설정 
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

		// InputMode 및 마우스 커서 설정 복구
		FInputModeGameOnly Mode;
		SetInputMode(Mode);
		bShowMouseCursor = false;

		// 게임 일시정지 해제
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
	// 스킬 쿨타임 HUD UI에 보내기
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
	// 상호작용 UI 생성
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
	// 상호작용 UI 제거
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
	// InGameData UI 할당 X -> 생성
	if (!StageDatawidget_Instance) {
		StageDatawidget_Instance = CreateWidget<UUserWidget_InGameData>(this, StageDatawidget_Class);

		if (StageDatawidget_Instance) {
			// UI 초기셋팅 적용
			StageDatawidget_Instance->DefaultUISetting();
			// Exit 델리케이트에 CloseInGameData 연결
			StageDatawidget_Instance->OnExitInGameDataWidget.Clear();
			StageDatawidget_Instance->OnExitInGameDataWidget.AddUObject(this, &ATPSPlayerController::CloseInGameData);

			StageDatawidget_Instance->AddToViewport();

			// 처음 UI를 생성하여 띄울경우 UI 설정이 안되있는 경우 발생
			// 해결을 위해 생성하자마자 제거 이후 다시 띄워준다.
			CloseInGameData();
		}
	}

	// 이미 할당된 경우 UI를 띄워줌 
	if (StageDatawidget_Instance) {
		StageDatawidget_Instance->DefaultUISetting();
		StageDatawidget_Instance->OnExitInGameDataWidget.Clear();
		StageDatawidget_Instance->OnExitInGameDataWidget.AddUObject(this, &ATPSPlayerController::CloseInGameData);

		StageDatawidget_Instance->AddToViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// 인풋 모드 설정
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
	// InGameData UI 제거
	if (StageDatawidget_Instance) {
		StageDatawidget_Instance->RemoveFromViewport();

		// 인풋 모드 설정
		FInputModeGameOnly Mode;
		SetInputMode(Mode);
		bShowMouseCursor = false;
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

