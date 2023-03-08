// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IngameMenu_UserWidget.h"
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

	void OpenInGameMenu();
	void CloseInGameMenu();

	virtual void SetupInputComponent() override;


private:
	UPROPERTY(EditAnywhere, Category = HUD)
		TSubclassOf<class UHUD_UserWidget> Hud_widgetClass;

	UPROPERTY(EditAnywhere, Category = HUD)
		class UHUD_UserWidget* Hud;


	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class UIngameMenu_UserWidget> InGameMenu_Class;

	UPROPERTY(EditAnywhere, Category = UI)
		class UIngameMenu_UserWidget* InGameMenu_Instance;

};
