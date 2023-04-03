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

	void OpenHUD();

	void InputKeyESC();

	void OpenInGameMenu();
	void CloseInGameMenu();

	virtual void SetupInputComponent() override;

	void HUDCoolDownUpdate(
		float Def_CoolTime_Q, float currentCoolTime_Q,
		float Def_CoolTime_E, float currentCoolTime_E,
		float Def_CoolTime_1, float currentCoolTime_1,
		float Def_CoolTime_2, float currentCoolTime_2);

	void OpenInteractionUI();

	void CloseInteractionUI();

	// 전투 정보 Tap
	void InputKeyTap();

	void OpenInGameData();
	void CloseInGameData();

private:
	UPROPERTY(EditAnywhere, Category = HUD)
		TSubclassOf<class UHUD_UserWidget> Hud_widgetClass;

	UPROPERTY(EditAnywhere, Category = HUD)
		class UHUD_UserWidget* Hud;


	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class UIngameMenu_UserWidget> InGameMenu_Class;

	UPROPERTY(EditAnywhere, Category = UI)
		class UIngameMenu_UserWidget* InGameMenu_Instance;


	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class UUserWidget> InteractionUI_Class;

	UPROPERTY(EditAnywhere, Category = UI)
		class UUserWidget* InteractionUI_Instance;


	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class UUserWidget_InGameData> StageDatawidget_Class;

	UPROPERTY(EditAnywhere, Category = UI)
		class UUserWidget_InGameData* StageDatawidget_Instance;
	

	bool bOpenInGameMenu = false;
	bool bOpenStageDataMenu = false;
};
