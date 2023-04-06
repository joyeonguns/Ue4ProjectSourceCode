// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IngameMenu_UserWidget.h"
#include "UserWidget_InGameData.h"
#include "TPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATPSPlayerController();

	virtual void BeginPlay() override;

	class UHUD_UserWidget* GetHUD();

	// HUD 띄우기
	void OpenHUD();

	// ESC 버튼 입력
	void InputKeyESC();

	// InGameMenu 띄우기
	void OpenInGameMenu();
	// InGameMenu 닫기
	void CloseInGameMenu();

	virtual void SetupInputComponent() override;

	// 스킬 쿨다운 UI 설정
	void HUDCoolDownUpdate(
		float Def_CoolTime_Q, float currentCoolTime_Q,
		float Def_CoolTime_E, float currentCoolTime_E,
		float Def_CoolTime_1, float currentCoolTime_1,
		float Def_CoolTime_2, float currentCoolTime_2);

	// 상호작용 UI 띄우기
	void OpenInteractionUI();
	// 상호작용 UI 제거
	void CloseInteractionUI();

	// 전투 정보 Tap
	void InputKeyTap();

	// InGameData UI 띄우기
	void OpenInGameData();
	// InGameData UI 제거
	void CloseInGameData();

private:
	// HUD UI
	UPROPERTY(EditAnywhere, Category = HUD)
		TSubclassOf<class UHUD_UserWidget> Hud_widgetClass;

	UPROPERTY(EditAnywhere, Category = HUD)
		class UHUD_UserWidget* Hud;


	// InGameMenu UI
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class UIngameMenu_UserWidget> InGameMenu_Class;

	UPROPERTY(EditAnywhere, Category = UI)
		class UIngameMenu_UserWidget* InGameMenu_Instance;


	// 상호작용 UI
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class UUserWidget> InteractionUI_Class;

	UPROPERTY(EditAnywhere, Category = UI)
		class UUserWidget* InteractionUI_Instance;


	// InGameData UI
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class UUserWidget_InGameData> StageDatawidget_Class;

	UPROPERTY(EditAnywhere, Category = UI)
		class UUserWidget_InGameData* StageDatawidget_Instance;
	

	bool bOpenInGameMenu = false;
	bool bOpenStageDataMenu = false;
};
